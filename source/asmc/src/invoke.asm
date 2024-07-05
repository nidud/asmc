; INVOKE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include memalloc.inc
include parser.inc
include expreval.inc
include lqueue.inc
include assume.inc
include segment.inc
include listing.inc
include mangle.inc
include proc.inc
include qfloat.inc
include types.inc
include indirect.inc
include fastpass.inc
include hllext.inc

public  size_vararg

define NUMQUAL

.enum reg_used_flags {
    R0_USED       = 0x01,   ; register contents of AX/EAX/RAX is destroyed
    R0_H_CLEARED  = 0x02,   ; 16bit: high byte of R0 (=AH) has been set to 0
    R0_X_CLEARED  = 0x04,   ; 16bit: register R0 (=AX) has been set to 0
    R2_USED       = 0x08,   ; contents of DX is destroyed ( via CWD ); cpu < 80386 only
    }

.data

size_vararg     int_t 0     ; size of :VARARG arguments

regax           uint_t T_AX, T_EAX, T_RAX
win64regs       uint_8 T_RCX, T_RDX, T_R8, T_R9
elf64regs       uint_8 T_RDI, T_RSI, T_RDX, T_RCX, T_R8, T_R9

    .code

; get segment part of an argument
; v2.05: extracted from PushInvokeParam(),
; so it could be used by watc_param() as well.

GetSegmentPart proc __ccall uses rsi rdi rbx opnd:ptr expr, buffer:string_t, fullparam:string_t

    mov esi,T_NULL
    ldr rdi,opnd
    mov rax,[rdi].expr.sym
    mov rdx,[rdi].expr.override

    .if ( rdx )

        .if ( [rdx].asm_tok.token == T_REG )
            mov esi,[rdx].asm_tok.tokval
        .else
            tstrcpy( rdi, [rdx].asm_tok.string_ptr )
        .endif

    .elseif ( rax && [rax].asym.segm )

        mov rbx,[rax].asym.segm
        mov rcx,[rbx].dsym.seginfo

        .if ( [rcx].seg_info.segtype == SEGTYPE_DATA ||
              [rcx].seg_info.segtype == SEGTYPE_BSS )
            search_assume( rbx, ASSUME_DS, TRUE )
        .else
            search_assume( rbx, ASSUME_CS, TRUE )
        .endif
        .if ( eax != ASSUME_NOTHING )

            lea rsi,[rax+T_ES] ; v2.08: T_ES is first seg reg in special.h
        .else
            .if !GetGroup([rdi].expr.sym)
                mov rax,rbx
            .endif
            .if rax
                tstrcpy( buffer, [rax].asym.name )
            .else
                tstrcat( tstrcpy( buffer, "seg " ), fullparam )
            .endif
        .endif
    .elseif ( rax && [rax].asym.state == SYM_STACK )
        mov esi,T_SS
    .else
        tstrcat( tstrcpy( buffer, "seg " ), fullparam )
    .endif
    .return( rsi )

GetSegmentPart endp


    assume rbx:ptr asm_tok

SkipTypecast proc fastcall private uses rsi rdi rbx fullparam:string_t, i:int_t, tokenarray:ptr asm_tok

    mov  rdi,rcx
    imul ebx,edx,asm_tok
    add  rbx,tokenarray
    xor  eax,eax
    mov  [rdi],al

    .for ( : : rbx += asm_tok )

        .break .if (( [rbx].token == T_COMMA ) || ( [rbx].token == T_FINAL ) )
        .if (( [rbx+asm_tok].token == T_BINARY_OPERATOR ) && ( [rbx+asm_tok].tokval == T_PTR ) )
            add rbx,asm_tok
        .else
            mov rsi,[rbx].tokpos
            mov rcx,[rbx+asm_tok].tokpos
            sub rcx,rsi
            rep movsb
        .endif
    .endf
    stosb
    ret

SkipTypecast endp

;;
;; push one parameter of a procedure called with INVOKE onto the stack
;; - i       : index of the start of the parameter list
;; - tokenarray : token array
;; - proc    : the PROC to call
;; - curr    : the current parameter
;; - reqParam: the index of the parameter which is to be pushed
;; - r0flags : flags for register usage across params
;;
;; psize,asize: size of parameter/argument in bytes.
;;

PushInvokeParam proc __ccall private uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok, pproc:ptr dsym,
        curr:ptr dsym, reqParam:int_t, r0flags:ptr uint_t

  local currParm:int_t
  local psize:int_t
  local asize:int_t
  local pushsize:int_t
  local j:int_t
  local fptrsize:int_t
  local t_addr:int_t ;; ADDR operator found
  local opnd:expr
  local fastcall_id:int_t
  local r_ax:int_t
  local fullparam[MAX_LINE_LEN]:char_t
  local buffer[64]:char_t
  local Ofssize:byte
  local curr_cpu
  local t_regax:int_t
  local ParamId:int_t

    imul ebx,i,asm_tok
    add  rbx,tokenarray

    .for ( ecx = 0 : ecx <= reqParam : )

        .if ( [rbx].token == T_FINAL ) ; this is no real error!
            .return( ERROR )
        .endif
        .if ( [rbx].token == T_COMMA )
            inc ecx
        .endif
        add rbx,asm_tok
        inc i
    .endf
    mov currParm,ecx

    ;; if curr is NULL this call is just a parameter check

    mov rdi,curr
    .if ( rdi == NULL )
        .return( NOT_ERROR )
    .endif

    movzx ecx,ModuleInfo.Ofssize
    lea rax,regax
    mov eax,[rax+rcx*4]
    mov t_regax,eax

    mov eax,reqParam
    inc eax
    mov ParamId,eax

    mov eax,ModuleInfo.curr_cpu
    and eax,P_CPU_MASK
    mov curr_cpu,eax

    mov rsi,pproc
    mov fastcall_id,GetFastcallId( [rsi].asym.langtype )
    mov r_ax,T_EAX
    mov t_addr,FALSE

    mov psize,[rdi].asym.total_size

    ;; ADDR: the argument's address is to be pushed?

    .if ( [rbx].token == T_RES_ID && [rbx].tokval == T_ADDR )
        mov t_addr,TRUE
        .if ( [rdi].asym.mem_type != MT_ABS )
            add rbx,asm_tok
            inc i
        .endif
    .endif

    ;; copy the parameter tokens to fullparam

    .for ( rdx = rbx : [rdx].asm_tok.token != T_COMMA &&
           [rdx].asm_tok.token != T_FINAL: rdx+=asm_tok )
    .endf

    mov rsi,[rbx].tokpos
    mov rcx,[rdx].asm_tok.tokpos
    sub rcx,rsi
    lea rdi,fullparam
    rep movsb
    mov byte ptr [rdi],0

    mov rdi,curr
    .if ( [rdi].asym.mem_type == MT_ABS && t_addr )
        add rbx,asm_tok
        inc i
    .endif

    mov j,i
    mov rsi,pproc

    ;; v2.11: GetSymOfssize() doesn't work for state SYM_TYPE

    movzx eax,[rsi].asym.segoffsize
    .if [rsi].asym.state != SYM_TYPE
        GetSymOfssize(rsi)
    .endif
    mov Ofssize,al
    mov ecx,eax
    mov eax,2
    shl eax,cl
    add eax,2
    mov fptrsize,eax

    .if ( t_addr )

        ; v2.06: don't handle forward refs if -Zne is set

        .ifd ( EvalOperand( &j, tokenarray, TokenCount, &opnd, ModuleInfo.invoke_exprparm ) == ERROR )
            .return
        .endif

        imul ebx,j,asm_tok
        add  rbx,tokenarray

        ; DWORD (16bit) and FWORD(32bit) are treated like FAR ptrs
        ; v2.11: argument may be a FAR32 pointer ( psize == 6 ), while
        ; fptrsize may be just 4!

        .if ( psize > fptrsize && fptrsize > 4 )

            ; QWORD is NOT accepted as a FAR ptr

            asmerr( 2114, ParamId )
           .return(NOT_ERROR)
        .endif

        .if ( fastcall_id  )

            .ifd ( fast_param( pproc, reqParam, curr, t_addr, &opnd, &fullparam, r0flags )  )
               .return( NOT_ERROR )
            .endif
        .endif

        .if ( opnd.kind == EXPR_REG || opnd.flags & E_INDIRECT )

ifndef ASMC64

            .if ( [rdi].asym.is_far || psize == fptrsize ||
                ( [rdi].asym.sflags & S_ISVARARG && opnd.mem_type == MT_FAR ) )

                mov rcx,opnd.sym
                .if ( rcx && [rcx].asym.state == SYM_STACK )
                    AddLineQueue( " push ss" )
                .elseif ( opnd.override != NULL )
                    mov rcx,opnd.override
                    AddLineQueueX( " push %s", [rcx].asm_tok.string_ptr )
                .else
                    AddLineQueue( " push ds" )
                .endif
            .endif
endif
            AddLineQueueX( " lea %r, %s", t_regax, &fullparam )
            mov rcx,r0flags
            or  byte ptr [rcx],R0_USED
            AddLineQueueX( " push %r", t_regax )

        .else

         push_address:

            ; push segment part of address?
            ; v2.11: do not assume a far pointer if psize == fptrsize
            ; ( parameter might be near32 in a 16-bit environment )
            ; v2.16: also include far overrides in vararg arguments.

ifndef ASMC64

            mov cl,[rdi].asym.Ofssize
            mov eax,2
            shl eax,cl

            .if ( [rdi].asym.is_far || psize > eax ||
                ( [rdi].asym.sflags & S_ISVARARG && opnd.mem_type == MT_FAR ) )

                GetSegmentPart( &opnd, &buffer, &fullparam )
                .if ( eax )

                    ; v2.11: push segment part as WORD or DWORD depending on target's offset size
                    ; problem: "pushw ds" is not accepted, so just emit a size prefix.

                    .new reg:int_t = eax
                    .if ( Ofssize != ModuleInfo.Ofssize || ( [rdi].asym.Ofssize == USE16 && CurrWordSize > 2 ) )

                        AddLineQueue( " db 66h" )
                    .endif
                    AddLineQueueX( " push %r", reg )
                .else
                    AddLineQueueX( " push %s", &buffer )
                .endif
                .if ( [rdi].asym.sflags & S_ISVARARG )
                    add size_vararg,CurrWordSize
                .endif
            .endif

            ; push offset part of address

            .if ( curr_cpu < P_186 )

                AddLineQueueX(
                    " mov ax, offset %s\n"
                    " push ax", &fullparam )
                mov rcx,r0flags
                or  byte ptr [rcx],R0_USED

            .else

                mov rcx,opnd.sym
                .if ( opnd.Ofssize == USE_EMPTY && rcx )

                    GetSymOfssize( rcx )

                    .if ( [rdi].asym.sflags & S_ISVARARG )

                        mov opnd.Ofssize,al

                    .else

                        ; v2.16: opnd.Ofssize is set - by the evaluator - only in a few cases (not clear when exactly),
                        ; but here it might be needed.
                        ; Either display an error or make jwasm extend the offset size.
                        ; v2.17: causes regression in v2.16 if current ofssize is USE64, see adjustment below.

                        mov cl,al
                        mov eax,2
                        shl eax,cl
                        .if ( al != CurrWordSize )
                            mov opnd.Ofssize,cl
                        .endif
                    .endif
                .endif


                ; v2.04: expand 16-bit offset to 32
                ; v2.11: also expand if there's an explicit near32 ptr requested in 16-bit
                ; v2.17: regression in v2.16 if USE64 is active (invoke54.asm); "CurrWordSize > 2" changed to "CurrWordSize == 4"

                .if ( ( opnd.Ofssize == USE16 && CurrWordSize == 4 ) ||
                    ( [rdi].asym.Ofssize == USE32 && CurrWordSize == 2 ) )
                    AddLineQueueX( " pushd offset %s", &fullparam )
                .elseif ( CurrWordSize > 2 && [rdi].asym.Ofssize == USE16 &&
                        ( [rdi].asym.is_far || Ofssize == USE16 ) ) ; v2.11: added
                    AddLineQueueX( " pushw offset %s", &fullparam )
                .elseif ( CurrWordSize == 2 && opnd.Ofssize == USE32 && !( [rdi].asym.sflags & S_ISVARARG ) ) ; v2.16: added
                    AddLineQueueX( " pushw offset %s", &fullparam )
                .else
                    .if ( !( [rsi].asym.flags & S_ISINLINE && [rdi].asym.sflags & S_ISVARARG ) )

                        ; v2.13: in 64-bit you can't push a 64-bit offset

                        .if ( [rdi].asym.Ofssize == USE64 )

                            AddLineQueueX( " lea rax, %s", &fullparam )
                            AddLineQueueX( " push rax" )
                            mov rcx,r0flags
                            or  byte ptr [rcx],R0_USED
                        .else
                            AddLineQueueX( " push offset %s", &fullparam )
                        .endif

                        ; v2.04: a 32bit offset pushed in 16-bit code

                        .if ( [rdi].asym.sflags & S_ISVARARG && CurrWordSize == 2 && opnd.Ofssize > USE16 )
                            add size_vararg,CurrWordSize
                        .endif
                    .endif
                .endif
            .endif
endif
        .endif

        .if ( [rdi].asym.sflags & S_ISVARARG )
            movzx eax,CurrWordSize
            .if ( [rdi].asym.is_far )
                add eax,eax
            .endif
            add size_vararg,eax
        .endif

        .return( NOT_ERROR )
    .endif

    ; ! ADDR branch

    ; handle the <reg>::<reg> case here, the evaluator wont handle it

    .if ( [rbx].token == T_REG && [rbx+asm_tok].token == T_DBL_COLON && [rbx+asm_tok*2].token == T_REG )

        .new asize2:int_t

        ; for pointers, segreg size is assumed to be always 2

ifndef ASMC64

        .if ( GetValueSp( [rbx].tokval ) & OP_SR )

            mov asize2,2

            ; v2.11: if target and current src have different offset sizes,
            ; the push of the segment register must be 66h-prefixed!

            .if ( Ofssize != ModuleInfo.Ofssize || ( [rdi].asym.Ofssize == USE16 && CurrWordSize > 2 ) )

                AddLineQueue( " db 66h" )
            .endif
        .else
endif
            mov asize2,SizeFromRegister( [rbx].tokval )
ifndef ASMC64
        .endif
endif

        mov asize,SizeFromRegister( [rbx+asm_tok*2].tokval )

        ; v2.31.35: Watcom handles the two first sets

        .if ( asize2 != 8 && !fastcall_id ) ;( fastcall_id == FCT_WATCOMC + 1 && currParm < 3 ) )

            AddLineQueueX( " push %r", [rbx].tokval )
        .endif

        ; v2.04: changed

        mov eax,asize
        add eax,asize2
        .if ( ( [rdi].asym.sflags & S_ISVARARG ) && al != CurrWordSize )
            add size_vararg,asize2
        .else
            add asize,asize2
        .endif
        tstrcpy( &fullparam, [rbx+asm_tok*2].string_ptr )

        mov opnd.kind,EXPR_REG
        and opnd.flags,not E_INDIRECT
        mov opnd.sym,NULL
        mov opnd.base_reg,&[rbx+asm_tok*2] ; for error msg 'eax overwritten...'

    .else

        ; v2.06: don't handle forward refs if -Zne is set
        ; v2.31: ABS to const

        .if ( [rdi].asym.mem_type == MT_ABS )

            mov opnd.kind,EXPR_CONST
            mov opnd.mem_type,MT_ABS
            mov opnd.sym,NULL
            mov opnd.mbr,NULL
            mov opnd.base_reg,NULL

        .else

            .return .ifd EvalOperand( &j, tokenarray, TokenCount, &opnd,
                            ModuleInfo.invoke_exprparm ) == ERROR

            imul ebx,j,asm_tok
            add  rbx,tokenarray
        .endif

        ; for a simple register, get its size

        .if ( opnd.kind == EXPR_REG && !( opnd.flags & E_INDIRECT ) )

            mov rcx,opnd.base_reg
            mov asize,SizeFromRegister([rcx].asm_tok.tokval)

            ; v2.15: check if there's nothing behind the register.
            ; because if "indirect" is false, the checks may be too simple.

            .if ( j < TokenCount && [rbx].token != T_COMMA )
                or opnd.flags,E_INDIRECT
            .endif

        .elseif ( opnd.kind == EXPR_CONST || opnd.mem_type == MT_EMPTY )

            mov eax,psize
if 1
            ; v2.16: don't set asize = psize if argument is an address

            mov rcx,opnd.sym
            .if ( opnd.kind == EXPR_ADDR && opnd.inst == T_OFFSET && rcx )

                mov ecx,GetSymOfssize( rcx )
                mov eax,2
                shl eax,cl
            .endif
endif
            mov asize,eax

            ; v2.04: added, to catch 0-size params ( STRUCT without members )

            .if ( psize == 0 )

                .if !( [rdi].asym.sflags & S_ISVARARG )

                    asmerr( 2114, ParamId )
                .endif

                ; v2.07: for VARARG, get the member's size if it is a structured var

                mov rcx,opnd.mbr
                .if ( rcx && [rcx].asym.mem_type == MT_TYPE )
                    mov asize,SizeFromMemtype( [rcx].asym.mem_type, opnd.Ofssize, [rcx].asym.type )
                .endif
            .endif

if 0 ; Masm error up to v11, v12+ allow this..

            ; v2.18: error (vararg param used as argument?)

            mov rcx,opnd.sym
            .if ( rcx && [rcx].asym.state == SYM_STACK && [rcx].asym.sflags & S_ISVARARG )

                mov edx,reqParam
                inc edx
                asmerr( 2114, edx )
            .endif
endif

        .elseif ( opnd.mem_type != MT_TYPE )

            .if ( opnd.kind == EXPR_ADDR && !( opnd.flags & E_INDIRECT ) && opnd.sym &&
                     opnd.inst == EMPTY && ( opnd.mem_type == MT_NEAR || opnd.mem_type == MT_FAR ) )

                jmp push_address
            .endif

            ; v2.16: if type is MT_PTR, then SizeFromMemtype() cannot decide if pointer is near or far;
            ; see invoke47/49/50.asm;
            ; sym.isfar and sym.Ofssize are NOT set if state is SYM_INTERNAL ( fields overlapp with first_size )!

            .if ( opnd.kind == EXPR_ADDR && opnd.mem_type == MT_PTR && opnd.sym )

                mov rcx,opnd.sym
                .if ( [rcx].asym.state == SYM_EXTERNAL ) ; external symbol: see invoke50.asm

                    movzx edx,opnd.Ofssize
                    .if ( edx == USE_EMPTY )
                        mov dl,[rcx].asym.Ofssize
                    .endif
                    .if ( [rcx].asym.is_far )
                        mov ecx,MT_FAR
                    .else
                        mov ecx,MT_NEAR
                    .endif
                    SizeFromMemtype( cl, edx, NULL )

                .else

                    mov rdx,opnd.mbr
                    .if ( rdx )
                        mov rcx,rdx
                    .endif
                    mov eax,[rcx].asym.total_size
                    .if ( [rcx].asym.flags & S_ISARRAY )

                        mov ecx,[rcx].asym.total_length
                        xor edx,edx
                        div ecx
                    .endif
                .endif

            .else

                ; v2.16: init opnd.Ofssize only if NOT MT_PTR!

                .if ( opnd.Ofssize == USE_EMPTY )
                    mov opnd.Ofssize,ModuleInfo.Ofssize
                .endif
                SizeFromMemtype( opnd.mem_type, opnd.Ofssize, opnd.type )
            .endif
            mov asize,eax

        .else

            mov rcx,opnd.sym
            .if !rcx
                mov rcx,opnd.mbr
            .endif
            mov rcx,[rcx].asym.type
            mov asize,[rcx].asym.total_size
        .endif
    .endif

    movzx eax,CurrWordSize
    mov pushsize,eax

    .if ( [rdi].asym.sflags & S_ISVARARG )

        mov psize,asize
    .endif

    .if ( asize == 16 && opnd.mem_type == MT_REAL16 && pushsize == 4 )

        mov asize,psize
    .endif

    .if ( fastcall_id )

        .ifd ( fast_param( pproc, reqParam, curr, t_addr, &opnd, &fullparam, r0flags ) )

            .return( NOT_ERROR )
        .endif
    .endif

    .if ( ( asize > psize ) || ( asize < psize && [rdi].asym.mem_type == MT_PTR ) )

        asmerr( 2114, ParamId )
        .return( NOT_ERROR )
    .endif

    .if ( pushsize == 8 )

        mov r_ax,T_RAX
    .endif

    .if ( ( opnd.kind == EXPR_ADDR && opnd.inst != T_OFFSET ) ||
          ( opnd.kind == EXPR_REG && opnd.flags & E_INDIRECT ) )

        ;; catch the case when EAX has been used for ADDR,
        ;; and is later used as addressing register!

        mov rcx,r0flags
        mov rdx,opnd.base_reg
        mov rax,opnd.idx_reg

        .if ( byte ptr [rcx] && ( ( rdx != NULL &&
             ( [rdx].asm_tok.tokval == T_EAX || [rdx].asm_tok.tokval == T_RAX ) ) ||
             ( rax != NULL &&
             ( [rax].asm_tok.tokval == T_EAX || [rax].asm_tok.tokval == T_RAX ) ) ) )

            mov byte ptr [rcx],0
            asmerr( 2133 )
        .endif

        .if ( [rdi].asym.sflags & S_ISVARARG )

            mov eax,pushsize

            .if ( asize > eax )

                mov eax,asize
            .endif
            add size_vararg,eax
        .endif

        .if ( asize > pushsize )

            .new t_dw:int_t = T_WORD

            .if ( curr_cpu >= P_386 )

                mov pushsize,4
                mov t_dw,T_DWORD
            .endif

            ; in params like "qword ptr [rax]" the typecast
            ; has to be removed

            .if ( opnd.flags & E_EXPLICIT )

                SkipTypecast( &fullparam, i, tokenarray )
                and opnd.flags,not E_EXPLICIT
            .endif

ifndef ASMC64

            .while ( asize > 0 )

                .if ( asize & 2 )

                    ; ensure the stack remains dword-aligned in 32bit

                    .if ( ModuleInfo.Ofssize > USE16 )

                        ; v2.05: better push a 0 word?
                        ; ASMC v1.12: ensure the stack remains dword-aligned in 32bit

                        .if ( pushsize == 4 )

                            add size_vararg,2
                        .endif
                        movzx ecx,ModuleInfo.Ofssize
                        lea rdx,stackreg
                        mov edx,[rdx+rcx*4]
                        AddLineQueueX( " sub %r, 2", edx )
                    .endif

                    sub asize,2
                    AddLineQueueX( " push word ptr %s+%u", &fullparam, asize )

                .else

                    ; v2.23 if stack base is ESP

                    movzx ecx,ModuleInfo.Ofssize
                    lea rdx,ModuleInfo
                    mov ecx,[rdx].module_info.basereg[rcx*4]
                    mov edx,asize
                    mov eax,pushsize
                    sub edx,eax
                    sub asize,eax

                    .if ( CurrProc && ecx == T_ESP )

                        mov edx,eax
                    .endif
                    AddLineQueueX( " push %r ptr %s+%u", t_dw, &fullparam, edx )

                .endif
            .endw
endif
        .elseif ( asize < pushsize )

            .if ( psize > 4 && pushsize < 8 )

                asmerr( 2114, ParamId )
            .endif

            ; v2.11: added, use MOVSX/MOVZX if cpu >= 80386

            .if ( asize < 4 && psize > 2 && IS_SIGNED(opnd.mem_type) && curr_cpu >= P_386 )

                AddLineQueueX(
                    " movsx eax, %s\n"
                    " push %r", &fullparam, r_ax )

                mov rcx,r0flags
                mov byte ptr [rcx],R0_USED ; reset R0_H_CLEARED

            .else

                .switch ( opnd.mem_type )
                .case MT_BYTE
                .case MT_SBYTE

                    .if ( psize == 1 && !( [rdi].asym.sflags & S_ISVARARG ) )

                        AddLineQueueX(
                            " mov al, %s\n"
                            " push %r", &fullparam, t_regax )
ifndef ASMC64
                    .elseif ( pushsize == 2 ) ; 16-bit code?

                        .if ( opnd.mem_type == MT_BYTE )

                            .if ( psize == 4 )

                                .if ( curr_cpu < P_186 )

                                    mov rcx,r0flags
                                    .if ( !( byte ptr [rcx] & R0_X_CLEARED ) )
                                        AddLineQueue( " xor ax, ax" )
                                    .endif
                                    mov rcx,r0flags
                                    or byte ptr [rcx],( R0_X_CLEARED or R0_H_CLEARED )
                                    AddLineQueue( " push ax" )
                                .else
                                    AddLineQueue( " push 0" )
                                .endif
                            .endif

                            AddLineQueueX( " mov al, %s", &fullparam )
                            mov rcx,r0flags
                            .if ( !( byte ptr [rcx] & R0_H_CLEARED ) )

                                or byte ptr [rcx],R0_H_CLEARED
                                AddLineQueue( " mov ah, 0" )
                            .endif

                        .else

                            AddLineQueueX( " mov al, %s", &fullparam )

                            mov rcx,r0flags
                            mov byte ptr [rcx],0 ; reset AH_CLEARED
                            AddLineQueue( " cbw" )

                            .if ( psize == 4 )

                                AddLineQueue(
                                    " cwd\n"
                                    " push dx" )
                                mov rcx,r0flags
                                or byte ptr [rcx],R2_USED
                            .endif
                        .endif
                        AddLineQueue( " push ax" )
endif
                    .else

                        mov ecx,T_MOVSX
                        .if opnd.mem_type == MT_BYTE

                            mov ecx,T_MOVZX
                        .endif
                        AddLineQueueX(
                            " %r eax, %s\n"
                            " push %r", ecx, &fullparam, r_ax )
                    .endif

                    mov rcx,r0flags
                    or byte ptr [rcx],R0_USED
                    .endc

                .case MT_WORD
                .case MT_SWORD

                    .if ( opnd.mem_type == MT_WORD && ( ModuleInfo.masm_compat_gencode || psize == 2 ))

                        .if ( pushsize == 8 )

                            AddLineQueueX(
                                " mov ax, %s\n"
                                " push rax", &fullparam )
                            mov rcx,r0flags
                            mov byte ptr [rcx],R0_USED ; reset R0_H_CLEARED
ifndef ASMC64
                        .else
                            .if ( [rdi].asym.sflags & S_ISVARARG || psize != 2 )

                                AddLineQueue( " pushw 0" )
                            .else

                                movzx ecx,ModuleInfo.Ofssize
                                lea rdx,stackreg
                                mov edx,[rdx+rcx*4]
                                AddLineQueueX( " sub %r, 2", edx )
                            .endif
                            AddLineQueueX( " push %s", &fullparam )
endif
                        .endif
                    .else

                        mov ecx,T_MOVSX
                        .if ( opnd.mem_type == MT_WORD )
                            mov ecx,T_MOVZX
                        .endif
                        AddLineQueueX(
                            " %r eax, %s\n"
                            " push %r", ecx, &fullparam, r_ax )
                        mov rcx,r0flags
                        or byte ptr [rcx],R0_USED
                    .endif
                    .endc

                .case MT_DWORD
                .case MT_SDWORD

                    .if ( pushsize == 8 )

                        AddLineQueueX(
                            " mov eax, %s\n"
                            " push rax", &fullparam )
                        mov rcx,r0flags
                        or byte ptr [rcx],R0_USED
                       .endc
                    .endif

                .default

                    .if ( asize == 3 ) ; added v2.29

                        .if ( pushsize > 2 )

                            AddLineQueueX(
                                " mov al, byte ptr %s[2]\n"
                                " shl eax, 16\n"
                                " mov ax, word ptr %s\n"
                                " push %r", &fullparam, &fullparam, r_ax )
                        .else
                            AddLineQueueX(
                                " push word ptr %s[2]\n"
                                " push word ptr %s", &fullparam, &fullparam )
                        .endif
                    .else
                        AddLineQueueX( " push %s", &fullparam )
                    .endif
                .endsw
            .endif

        .else ; asize == pushsize

            .if ( IS_SIGNED(opnd.mem_type) && psize > asize )

                .if ( psize > 2 && ( curr_cpu >= P_386 ) )

                    AddLineQueueX(
                        " movsx eax, %s\n"
                        " push %r", &fullparam, r_ax )
                    mov rcx,r0flags
                    mov byte ptr [rcx],R0_USED ; reset R0_H_CLEARED
ifndef ASMC64
                .elseif ( pushsize == 2 && psize > 2 )

                    AddLineQueueX(
                        " mov ax, %s\n"
                        " cwd\n"
                        " push dx\n"
                        " push ax", &fullparam )
                    mov rcx,r0flags
                    mov byte ptr [rcx],R0_USED or R2_USED
endif
                .else
                    AddLineQueueX( " push %s", &fullparam )
                .endif
            .else
ifndef ASMC64
                .if ( pushsize == 2 && psize > 2 )

                    .if ( curr_cpu < P_186 )

                        mov rcx,r0flags
                        .if ( !( byte ptr [rcx] & R0_X_CLEARED ) )

                            AddLineQueue( " xor ax, ax" )
                        .endif
                        AddLineQueue( " push ax" )
                        mov rcx,r0flags
                        or byte ptr [rcx],( R0_USED or R0_X_CLEARED or R0_H_CLEARED )
                    .else
                        AddLineQueue( " pushw 0" )
                    .endif
                .endif
endif
                AddLineQueueX( " push %s", &fullparam )
            .endif
        .endif

    .else  ; the parameter is a register or constant value!

        .if ( opnd.kind == EXPR_REG )

           .new reg:int_t
            mov rcx,opnd.base_reg
            mov eax,[rcx].asm_tok.tokval
            mov reg,eax

           .new optype:dword = GetValueSp(eax)

            ; v2.11
            .if ( [rdi].asym.sflags & S_ISVARARG && psize < pushsize )

                mov psize,pushsize
            .endif

            ; v2.06: check if register is valid to be pushed.
            ; ST(n), MMn, XMMn, YMMn and special registers are NOT valid!

            .if ( optype & ( OP_STI or OP_MMX or OP_XMM or OP_YMM or OP_ZMM or OP_RSPEC ) )

                .return( asmerr( 2114, ParamId ) )
            .endif

            mov rcx,r0flags
            .if ( ( byte ptr [rcx] & R0_USED ) && ( reg == T_AH || ( optype & OP_A ) ) )

                and byte ptr [rcx],not R0_USED
                asmerr( 2133 )

            .elseif ( ( byte ptr [rcx] & R2_USED ) && ( reg == T_DH || GetRegNo(reg) == 2 ) )

                and byte ptr [rcx],not R2_USED
                asmerr( 2133 )
            .endif

            mov edx,2
            mov cl,Ofssize
            shl edx,cl
            .if ( asize != psize || asize < edx )

                ; register size doesn't match the needed parameter size.

                .if ( psize > 4 && pushsize < 8 )

                    asmerr( 2114, ParamId )
                .endif

                .if ( asize <= 2 && ( psize == 4 || pushsize == 4 ) )

                    .if ( curr_cpu >= P_386 && asize == psize )

                        .if ( asize == 2 )

                            sub reg,T_AX
                            add reg,T_EAX
                        .else

                            ; v2.11: hibyte registers AH, BH, CH, DH
                            ; ( no 4-7 ) needs special handling

                            .if ( reg < T_AH )

                                sub reg,T_AL
                                add reg,T_EAX
                            .else

                                AddLineQueueX( " mov al, %s", &fullparam )
                                mov rcx,r0flags
                                or byte ptr [rcx],R0_USED
                                mov reg,T_EAX
                            .endif
                            mov asize,2
                        .endif
ifndef ASMC64
                    .elseif ( IS_SIGNED( opnd.mem_type ) && pushsize < 4 )

                        ; psize is 4 in this branch

                        .if ( curr_cpu >= P_386 )

                            AddLineQueueX( " movsx eax, %s", &fullparam )
                            mov rcx,r0flags
                            mov byte ptr [rcx],R0_USED
                            mov reg,T_EAX

                        .else

                            mov rcx,r0flags
                            mov byte ptr [rcx],R0_USED or R2_USED
                            .if ( asize == 1 )

                                .if ( reg != T_AL )

                                    AddLineQueueX( " mov al, %s", &fullparam )
                                .endif
                                AddLineQueue( " cbw" )
                            .elseif ( reg != T_AX )

                                AddLineQueueX( " mov ax, %s", &fullparam )
                            .endif
                            AddLineQueue(
                                " cwd\n"
                                " push dx" )
                            mov reg,T_AX

                        .endif
                        mov asize,2 ; done

                    .elseif ( curr_cpu >= P_186 )

                        .if ( pushsize == 4 )

                            .if ( asize == 1 )

                                ; handled below

                            .elseif ( psize <= 2 )

                                movzx ecx,ModuleInfo.Ofssize
                                lea rdx,stackreg
                                mov edx,[rdx+rcx*4]
                                AddLineQueueX( " sub %r, 2", edx )

                            .elseif ( IS_SIGNED( opnd.mem_type ) )

                                AddLineQueueX( " movsx eax, %s", &fullparam )
                                mov rcx,r0flags
                                mov byte ptr [rcx],R0_USED
                                mov reg,T_EAX
                            .else
                                AddLineQueue( " pushw 0" )
                            .endif
                        .else
                            AddLineQueue( " pushw 0" )
                        .endif

                    .else

                        mov rcx,r0flags
                        .if ( !( byte ptr [rcx] & R0_X_CLEARED ) )

                            ; v2.11: extra check needed

                            .if ( reg == T_AH || ( optype & OP_A ) )

                                asmerr( 2133 )
                            .endif
                            AddLineQueue( " xor ax, ax" )
                        .endif

                        AddLineQueue( " push ax" )
                        mov rcx,r0flags
                        mov byte ptr [rcx],R0_USED or R0_H_CLEARED or R0_X_CLEARED
endif
                    .endif

                .elseif ( pushsize == 8 && ( ( asize == psize && psize < 8 ) ||
                            ( asize == 4 && psize == 8 ) ) )

                    SizeFromRegister(reg)
                    mov ecx,reg
                    .switch eax
                    .case 1
                        .if ( ecx >= T_AL && ecx <= T_BH )
                            add ecx,(T_RAX - T_AL)
                        .elseif ( ecx >= T_SPL && ecx <= T_DIL )
                            add ecx,(T_RSP - T_SPL)
                        .elseif ( ecx >= T_R8B && ecx <= T_R15B )
                            add ecx,(T_R8 - T_R8B)
                        .endif
                        .endc
                    .case 2
                        .if ( ecx >= T_AX && ecx <= T_DI )
                            add ecx,(T_RAX - T_AX)
                        .elseif ( ecx >= T_R8W && ecx <= T_R15W )
                            add ecx,(T_R8 - T_R8W)
                        .endif
                        .endc
                    .case 4
                        .if ( ecx >= T_EAX && ecx <= T_EDI )
                            add ecx,(T_RAX - T_EAX)
                        .elseif ( ecx >= T_R8D && ecx <= T_R15D )
                            add ecx,(T_R8 - T_R8D)
                        .endif
                        .endc
                    .endsw
                    mov reg,ecx
                .endif

                .if ( asize == 1 )

                    mov eax,reg
                    .if ( ( eax >= T_AH && eax <= T_BH ) || psize != 1 )

                        .if ( psize != 1 && curr_cpu >= P_386 )

                            ; v2.10: consider signed type coercion!

                            mov eax,R0_USED or R0_H_CLEARED
                            mov ecx,T_MOVZX
                            .if IS_SIGNED(opnd.mem_type)

                                mov ecx,T_MOVSX
                                mov eax,R0_USED
                            .endif

                            mov rdx,r0flags
                            mov [rdx],al
                            AddLineQueueX( " %r %r, %s", ecx, t_regax, &fullparam )

                        .else

                            .if ( eax != T_AL )

                                AddLineQueueX( " mov al, %s", &fullparam )

                                mov rcx,r0flags
                                or  byte ptr [rcx],R0_USED
                                and byte ptr [rcx],not R0_X_CLEARED
                            .endif

                            .if ( psize != 1 ) ; v2.11: don't modify AH if paramsize is 1

                                mov rcx,r0flags
                                .if ( IS_SIGNED( opnd.mem_type ) )

                                    and byte ptr [rcx],not ( R0_H_CLEARED or R0_X_CLEARED )
                                    AddLineQueue( " cbw" )

                                .elseif ( !( byte ptr [rcx] & R0_H_CLEARED ) )

                                    or byte ptr [rcx],R0_H_CLEARED
                                    AddLineQueue( " mov ah, 0" )
                                .endif
                            .endif
                        .endif
                        mov reg,t_regax

                    .else

                        ; convert 8-bit to 16/32-bit register name

                        .if ( ( curr_cpu >= P_386) && ( psize == 4 || pushsize == 4 ) )

                            sub eax,T_AL
                            add eax,T_EAX

                        .elseif ( pushsize == 8 && curr_cpu >= P_64 )

                            .if ( eax >= T_AL && eax <= T_BL )

                                sub eax,T_AL
                                add eax,T_RAX

                            .elseif ( eax >= T_SPL && eax <= T_DIL )

                                sub eax,T_SPL
                                add eax,T_RSP
                            .else
                                sub eax,T_R8B
                                add eax,T_R8
                            .endif

                        .elseif ( pushsize < 8 )

                            sub eax,T_AL
                            add eax,T_AX
                        .endif
                        mov reg,eax
                    .endif
                .endif
            .endif

            AddLineQueueX( " push %r", reg )

            ; v2.05: don't change psize if > pushsize

            .if ( psize < pushsize )

                ; v2.04: adjust psize ( for siz_vararg update )

                mov psize,pushsize
            .endif

        .else ; constant value

            ; v2.06: size check

            .if ( psize )

                mov eax,opnd.value
                mov edx,opnd.hvalue

                .if ( opnd.kind == EXPR_FLOAT )
                    mov ecx,4
                .elseif ( ( !edx && eax <= 255 ) || ( edx == -1 && sdword ptr eax >= -255 ) )
                    mov ecx,1
                .elseif ( ( !edx && eax <= 65535 ) || ( edx == -1 && sdword ptr eax >= -65535 ) )
                    mov ecx,2
                .elseif ( !edx || edx == -1 )
                    mov ecx,4
                .else
                    mov ecx,8
                .endif
                .if ( psize < ecx )
                    asmerr( 2114, ParamId )
                .endif
            .endif

            mov eax,2
            mov cl,Ofssize
            shl eax,cl
            mov asize,eax

            .if ( psize < eax ) ; ensure that the default argsize (2,4,8) is met

                .if ( psize == 0 && [rdi].asym.sflags & S_ISVARARG )

                    ; v2.04: push a dword constant in 16-bit

                    .if ( eax == 2 &&
                        ( opnd.value > 0xFFFF || opnd.value < -65535 ) )

                        mov psize,4
                    .else
                        mov psize,eax
                    .endif
                .else
                    mov psize,eax
                .endif
            .endif

            .if ( curr_cpu < P_186 )
ifndef ASMC64p
                mov rcx,r0flags
                or byte ptr [rcx],R0_USED

                .switch ( psize )
                .case 2
                    .if ( opnd.value != 0 || opnd.kind == EXPR_ADDR )

                        AddLineQueueX( " mov ax, %s", &fullparam )
                    .else
                        .if ( !( byte ptr [rcx] & R0_X_CLEARED ) )

                            AddLineQueue( " xor ax, ax" )
                        .endif

                        mov rcx,r0flags
                        or byte ptr [rcx],R0_H_CLEARED or R0_X_CLEARED
                    .endif
                    .endc

                .case 4
                    .if ( opnd.uvalue <= 0xFFFF )

                        AddLineQueue( " xor ax, ax" )
                    .else
                        AddLineQueueX( " mov ax, highword (%s)", &fullparam )
                    .endif
                    AddLineQueue( " push ax" )

                    .if ( opnd.uvalue != 0 || opnd.kind == EXPR_ADDR )

                        AddLineQueueX( " mov ax, lowword (%s)", &fullparam )
                    .else
                        mov rcx,r0flags
                        or byte ptr [rcx],R0_H_CLEARED or R0_X_CLEARED
                    .endif
                    .endc
                .default
                    asmerr( 2114, ParamId )
                .endsw
                AddLineQueue( " push ax" )
endif
            .else ; cpu >= 80186

                mov ebx,T_PUSH
                mov esi,EMPTY

                .if ( psize != pushsize )

                    .switch psize
                    .case 2

                        mov ebx,T_PUSHW
                        .endc

                    .case 6 ; v2.04: added

                        ; v2.11: use pushw only for 16-bit target
ifndef ASMC64
                        .if ( Ofssize == USE16 )

                            mov ebx,T_PUSHW
                        .elseif ( Ofssize == USE32 && CurrWordSize == 2 )

                            mov ebx,T_PUSHD
                        .endif
endif
                        AddLineQueueX( " %r (%s) shr 32t", ebx, &fullparam )

                        ; no break

                    .case 4
ifndef ASMC64
                        .if ( curr_cpu >= P_386 )

                            mov ebx,T_PUSHD
                        .else
                            mov ebx,T_PUSHW
                            AddLineQueueX( " pushw highword (%s)", &fullparam )
                            mov esi,T_LOWWORD
                        .endif
endif
                        .endc

                        ; v2.25: added support for REAL10 and REAL16

                    .case 10

                        .if ( Ofssize == USE16 || Options.strict_masm_compat == TRUE ||
                              opnd.kind != EXPR_FLOAT )
                            .endc
                        .endif

                        quad_resize( &opnd, 10)
                        AddLineQueueX( " push 0x%x", opnd.h64_l )

                        .if ( curr_cpu >= P_64 )

                            mov rcx,r0flags
                            or byte ptr [rcx],R0_USED
                            AddLineQueueX(
                                " mov rax, 0x%lx\n"
                                " push rax", opnd.llvalue )
ifndef ASMC64
                        .else

                            mov ebx,T_PUSHD
                            AddLineQueueX(
                                " pushd high32 (0x%lx)\n"
                                " pushd low32 (0x%lx)", opnd.llvalue,  opnd.llvalue )
endif
                        .endif
                        jmp skip_push

                    .case 16

                        .endc .if ( Ofssize == USE16 || Options.strict_masm_compat == TRUE )
ifndef ASMC64
                        .if ( Ofssize == USE32 )

                            mov ebx,T_PUSHD
                            AddLineQueueX(
                                " pushd high32 (0x%lx)\n"
                                " pushd low32 (0x%lx)\n"
                                " pushd high32 (0x%lx)\n"
                                " pushd low32 (0x%lx)", opnd.hlvalue,  opnd.hlvalue, opnd.llvalue,  opnd.llvalue )
                            jmp skip_push
                        .endif
endif
                        .if ( opnd.h64_h == 0 || opnd.h64_h == -1 )

                            AddLineQueueX( " push 0x%lx", opnd.hlvalue )
                        .else

                            mov rcx,r0flags
                            or byte ptr [rcx],R0_USED
                            AddLineQueueX(
                                " mov rax, 0x%lx\n"
                                " push rax", opnd.hlvalue )
                        .endif

                        .if ( opnd.l64_h == 0 || opnd.l64_h == -1 )

                            AddLineQueueX( " push 0x%lx", opnd.llvalue )
                        .else

                            mov rcx,r0flags
                            or byte ptr [rcx],R0_USED
                            AddLineQueueX(
                                " mov rax, 0x%lx\n"
                                " push rax", opnd.llvalue )
                        .endif
                        jmp skip_push

                    .case 8

                        ; v2.13: .x64 doesn't mean that the current segment is 64-bit

                        .endc .if ( Ofssize == USE64 )
ifndef ASMC64
                        ; v2.06: added support for double constants

                        .if ( opnd.kind == EXPR_CONST || opnd.kind == EXPR_FLOAT )

                            mov ebx,T_PUSHD
                            mov esi,T_LOW32
                            AddLineQueueX( " pushd high32 (%s)", &fullparam )
                           .endc
                        .endif
endif

                    .default
                        asmerr( 2114, ParamId )
                    .endsw
                .endif

                .if ( esi != EMPTY )

                    AddLineQueueX( " %r %r (%s)", ebx, esi, &fullparam )
                .else
                    AddLineQueueX( " %r %s", ebx, &fullparam )
                .endif

            .endif
        .endif

skip_push:

        .if ( [rdi].asym.sflags & S_ISVARARG )

            add size_vararg,psize
        .endif

    .endif
    .return( NOT_ERROR )

PushInvokeParam endp


get_regname proc __ccall reg:int_t, size:int_t

    mov reg,get_register( reg, size )
    GetResWName( reg, LclAlloc(8) )
    ret

get_regname endp

; generate a call for a prototyped procedure

InvokeDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

   .new sym:ptr asym
   .new pproc:ptr dsym
   .new arg:ptr dsym
   .new p:string_t
   .new q:string_t
   .new numParam:int_t
   .new value:int_t
   .new size:int_t
   .new parmpos:int_t
   .new namepos:int_t
   .new porder:int_t
   .new j:int_t
   .new r0flags:uint_t = 0
   .new info:ptr proc_info
   .new curr:ptr dsym
   .new opnd:expr
   .new buffer[MAX_LINE_LEN]:char_t
   .new fastcall_id:int_t
   .new pmacro:ptr asym = NULL
   .new pclass:ptr asym
   .new struct_ptr:ptr asm_tok = NULL

    inc i ; skip INVOKE directive
    mov namepos,i

    .if ( Options.strict_masm_compat == 0 )
        .while 1
            .return .ifd ( ExpandHllProc( &buffer, i, tokenarray ) == ERROR )
            .break  .if !buffer

            QueueTestLines( &buffer )
            RunLineQueue()
            mov rbx,tokenarray
            .if ( [rbx].tokval == T_INVOKE && [rbx+asm_tok].token == T_REG && TokenCount == 2 )
                .return NOT_ERROR
            .endif
        .endw
    .endif

    imul ebx,i,asm_tok
    add rbx,tokenarray

    assume rsi:ptr asym

    ; if there is more than just an ID item describing the invoke target,
    ; use the expression evaluator to get it

    .if ( [rbx].token != T_ID || ( [rbx+asm_tok].token != T_COMMA && [rbx+asm_tok].token != T_FINAL ) )

        .return .ifd EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR

        mov rsi,opnd.type
        .if ( rsi != NULL && [rsi].state == SYM_TYPE )
            mov sym,rsi
            mov pproc,rsi
            .if ( [rsi].mem_type == MT_PROC ) ; added for v1.95
                jmp isfnproto
            .endif
            .if ( [rsi].mem_type == MT_PTR ) ; v2.09: mem_type must be MT_PTR
                jmp isfnptr
            .endif
        .endif
        .if ( opnd.kind == EXPR_REG )
            mov rbx,opnd.base_reg
            .if ( GetValueSp( [rbx].tokval ) & OP_RGT8 )
                mov sym,GetStdAssume( GetRegNo( [rbx].tokval ) )
            .else
                mov sym,NULL
            .endif
        .else
            mov rax,opnd.mbr
            .if rax == NULL
                mov rax,opnd.sym
            .endif
            mov sym,rax
        .endif

    .else
        mov opnd.base_reg,NULL
        imul ebx,i,asm_tok
        add rbx,tokenarray

        mov sym,SymSearch( [rbx].string_ptr )
        inc i
    .endif

    mov rsi,sym
    .if ( rsi == NULL )
        ; v2.04: msg changed
        .return( asmerr( 2190 ) )
    .endif
    mov rdx,[rsi].type
    mov rcx,[rsi].target_type
    .if ( [rsi].flags & S_ISPROC ) ;; the most simple case: symbol is a PROC
    .elseif ( [rsi].mem_type == MT_PTR && rcx && [rcx].asym.flags & S_ISPROC )
        mov sym,rcx
    .elseif ( [rsi].mem_type == MT_PTR && rcx && [rcx].asym.mem_type == MT_PROC )
        mov pproc,rcx
        jmp isfnproto
    .elseif ( ( [rsi].mem_type == MT_TYPE ) && ( [rdx].asym.mem_type == MT_PTR || [rdx].asym.mem_type == MT_PROC ) )
        ; second case: symbol is a (function?) pointer
        mov pproc,rdx
        .if ( [rdx].asym.mem_type != MT_PROC )
            jmp isfnptr
        .endif
    isfnproto:
        ; pointer target must be a PROTO typedef
        mov rsi,pproc
        .if [rsi].mem_type != MT_PROC
            .return( asmerr( 2190 ) )
        .endif
    isfnptr:
        ;; get the pointer target
        mov rsi,pproc
        mov sym,[rsi].target_type
        .if ( rax == NULL )
            .return( asmerr( 2190 ) )
        .endif
    .else
        .return( asmerr( 2190 ) )
    .endif
    mov rsi,sym
    mov pproc,rsi
    mov rcx,rsi
    mov info,[rcx].dsym.procinfo

    .if ( Options.strict_masm_compat == 0 )

        imul ebx,namepos,asm_tok
        add rbx,tokenarray
        mov rcx,[rsi].target_type
        .if ( [rsi].state == SYM_EXTERNAL &&
              rcx && [rcx].asym.state == SYM_MACRO )

            mov rax,[rcx].asym.altname
            .if ( rax )
                mov pmacro,rcx
                mov [rax],rcx
                tstrcpy( &buffer, [rcx].asym.name )
            .endif

        .elseif ( [rbx].token == T_OP_SQ_BRACKET &&
                  [rbx+3*asm_tok].token == T_DOT && opnd.mbr )

            mov rdi,opnd.mbr
            .if ( [rdi].asym.flags & S_METHOD )

                mov pclass,SymSearch( [rbx+4*asm_tok].string_ptr )

                .if ( rax && [rax].asym.flags & S_ISVTABLE )

                    .if ( [rdi].asym.flags & S_VMACRO )

                        mov pmacro,[rdi].asym.vmacro
                        tstrcpy( &buffer, [rax].asym.name )
                    .else
                        mov rcx,[rax].asym.class
                        tstrcat( tstrcat( tstrcpy( &buffer, [rcx].asym.name ), "_" ), [rdi].asym.name )
                        mov pmacro,SymSearch(rax)
                    .endif

                    mov rax,pmacro
                    .if ( rax && [rax].asym.state == SYM_TMACRO )
                        mov pmacro,SymSearch( [rax].asym.string_ptr )
                    .endif
                    .if ( rax && [rax].asym.state != SYM_MACRO )
                        mov pmacro,NULL
                    .endif

                .endif

                .if ( [rdi].asym.flags & S_VPARRAY )

                    and [rdi].asym.flags,not S_VPARRAY

                    mov  ecx,TokenCount
                    dec  ecx
                    imul edx,ecx,asm_tok
                    add  rdx,tokenarray

                    .while ( rdx > rbx )
                        .break .if [rdx].asm_tok.token == T_COMMA
                        sub rdx,asm_tok
                        dec ecx
                    .endw
                    .if ( [rdx].asm_tok.token == T_COMMA )

                        lea rax,[rdx+asm_tok]
                        mov struct_ptr,rax
                        mov [rdx].asm_tok.token,T_FINAL
                        mov TokenCount,ecx
                    .endif
                .endif
            .endif

            or [rsi].flags,S_METHOD
            .if ( pmacro )
                or [rsi].flags,S_ISINLINE
                .if ( [rax].asym.flags & S_ISSTATIC )
                    or [rsi].flags,S_ISSTATIC
                .endif
            .endif
        .endif
    .endif

    mov rdx,info
    .for ( rcx = [rdx].proc_info.paralist, numParam = 0 : rcx : \
           rcx = [rcx].dsym.nextparam, numParam++ )
    .endf

    mov j,i
    .if ( [rsi].flags & S_ISSTATIC )
        inc i
        imul ebx,i,asm_tok
        add rbx,tokenarray
        .for ( : [rbx].token != T_FINAL && [rbx].token != T_COMMA : i++, rbx+=asm_tok )
        .endf
    .endif

    mov fastcall_id,GetFastcallId( [rsi].langtype )

    .if ( fastcall_id )

        fastcall_init()
        fast_fcstart( rsi, numParam, i, tokenarray, &value )
        mov porder,eax
    .endif

    mov rdx,info
    assume rdi:ptr dsym
    mov rdi,[rdx].proc_info.paralist
    mov parmpos,i

    .if ( !( [rdx].proc_info.flags & PROC_HAS_VARARG ) )

        ; check if there is a superfluous parameter in the INVOKE call
        .ifd ( PushInvokeParam( i, tokenarray, pproc, NULL, numParam, &r0flags ) != ERROR )
            .return( asmerr( 2136 ) )
        .endif
    .else

       .new k:int_t
        mov eax,TokenCount
        sub eax,i
        shr eax,1
        mov k,eax

        ;; for VARARG procs, just push the additional params with
        ;; the VARARG descriptor

        dec numParam
        mov size_vararg,0 ;; reset the VARARG parameter size count

        .while ( rdi && !( [rdi].sflags & S_ISVARARG ) )
            mov rdi,[rdi].nextparam
        .endw
        .for ( : k >= numParam: k-- )
            PushInvokeParam( i, tokenarray, pproc, rdi, k, &r0flags )
        .endf

        ;; move to first non-vararg parameter, if any

        mov rdx,info
        .for ( rdi = [rdx].proc_info.paralist : rdi && [rdi].sflags & S_ISVARARG : rdi = [rdi].nextparam )

        .endf
    .endif

    ; the parameters are usually stored in "push" order.
    ; This if() must match the one in proc.asm, ParseParams().

    .ifd GetParamDirection(rsi)

        ; v2.23 if stack base is ESP

        .new total:int_t = 0

        .for ( : rdi && numParam : rdi = [rdi].nextparam )
            dec numParam
            .ifd ( PushInvokeParam( i, tokenarray, pproc, rdi, numParam, &r0flags ) == ERROR )
                .if ( !pmacro )
                    asmerr( 2033, numParam )
                .endif
            .endif

            movzx eax,ModuleInfo.Ofssize
            lea rcx,ModuleInfo
            mov eax,[rcx].module_info.basereg[rax*4]
            .if ( CurrProc && eax == T_ESP )

                ; The symbol offset is reset after the loop.
                ; To have any effect the push-lines needs to
                ; be processed here for each argument.

                RunLineQueue()

                ; set push size to DWORD/QWORD

                mov eax,[rdi].total_size
                .if (eax < 4)
                    mov eax,4
                .endif
                .if (eax > 4)
                    mov eax,8
                .endif
                add total,eax

                ; Update arguments in the current proc if any

                mov rcx,CurrProc
                mov rdx,[rcx].dsym.procinfo
                mov rdx,[rdx].proc_info.paralist
                .for ( : rdx : rdx = [rdx].dsym.nextparam )
                    .if ( [rdx].asym.state != SYM_TMACRO )
                        add [rdx].asym.offs,eax
                    .endif
                .endf
            .endif
        .endf

        .if ( total )

            mov rcx,CurrProc
            mov rax,[rcx].dsym.procinfo
            mov rdx,[rax].proc_info.paralist

            .for ( : rdx : rdx = [rdx].dsym.nextparam )
                .if ( [rdx].asym.state != SYM_TMACRO )
                    sub [rdx].asym.offs,total
                .endif
            .endf
        .endif

    .else
        .for ( numParam = 0 : rdi && !( [rdi].sflags & S_ISVARARG ) : rdi = [rdi].nextparam, numParam++ )
            .ifd ( PushInvokeParam( i, tokenarray, pproc, rdi, numParam, &r0flags ) == ERROR )
                .if ( !pmacro )
                    asmerr( 2033, numParam )
                .endif
            .endif
        .endf
    .endif

    mov i,j

    mov rdx,info
    mov rcx,pproc
    .if ( !pmacro && [rcx].asym.langtype == LANG_SYSCALL &&
          [rdx].proc_info.flags & PROC_HAS_VARARG && ModuleInfo.Ofssize == USE64 )

         .if ( porder )
            AddLineQueueX( " mov eax, %d", porder )
         .else
            AddLineQueue ( " xor eax, eax" )
         .endif
    .endif

    ; v2.05 added. A warning only, because Masm accepts this.

    mov rcx,pproc
    mov rdx,opnd.base_reg
    .if ( opnd.base_reg != NULL && Parse_Pass == PASS_1 && \
        (r0flags & R0_USED ) && [rdx].asm_tok.bytval == 0 && !( [rcx].asym.flags & S_METHOD ) )
        asmerr( 7002 )
    .endif

    mov p,StringBufferEnd
    tstrcpy( p, " call " )
    add p,6

    .if ( !pmacro && [rsi].state == SYM_EXTERNAL && [rsi].dll )

       .new iatname:ptr = p
        tstrcpy( p, ModuleInfo.imp_prefix )
        add p,tstrlen( p )
        add p,Mangle( rsi, p )
        inc namepos
        .if ( !( [rsi].flags & S_IAT_USED ) )
            or [rsi].flags,S_IAT_USED
            mov rcx,[rsi].dll
            inc [rcx].dll_desc.cnt
            .if ( [rsi].langtype != LANG_NONE && [rsi].langtype != ModuleInfo.langtype )
                movzx eax,[rsi].langtype
                add eax,T_CCALL - 1
                AddLineQueueX( " externdef %r %s: ptr proc", eax, iatname )
            .else
                AddLineQueueX( " externdef %s: ptr proc", iatname )
            .endif
        .endif
    .endif

    imul ebx,namepos,asm_tok
    add rbx,tokenarray
    mov rcx,opnd.mbr
    .if ( pmacro || ( [rbx].token == T_OP_SQ_BRACKET &&
          [rbx+3*asm_tok].token == T_DOT && rcx && [rcx].asym.flags & S_METHOD ) )

        .if ( pmacro )

           .new cnt:int_t = 0
           .new args[64]:string_t
           .new regname[16]:sbyte

            mov rcx,StringBufferEnd
            inc rcx
            mov p,rcx
            tstrcpy( p, &buffer )
            tstrcat( p, "( " )
            add p,tstrlen(p)

            .if ( fastcall_id )

                .for ( rdx = info, rdi = [rdx].proc_info.paralist: rdi: rdi = [rdi].nextparam, cnt++ )

                    mov rax,[rdi].name
                    .if ( [rdi].mem_type == MT_ABS )
                        lea rdx,@CStr("")
                        mov [rdi].name,rdx
                    .elseif ( [rdi].state == SYM_TMACRO )
                        mov rax,[rdi].string_ptr
                    .elseif ( [rdi].flags & S_REGPARAM )
                        movzx ecx,[rdi].param_reg
                        LclDup( GetResWName(ecx, &regname) )
                    .else
                        movzx eax,[rdi].Ofssize
                        lea   rdx,stackreg
                        mov   edx,[rdx+rax*4]
                        movzx ecx,[rdi].param_offs
                        tsprintf( &regname, "[%r+%u]", edx, ecx )
                        LclDup( &regname )
                    .endif
                    movzx ecx,[rdi].param_id
                    mov args[rcx*string_t],rax
                .endf
            .endif

            imul ebx,i,asm_tok
            add rbx,tokenarray
            mov rdx,info
            mov rdi,pproc

            .if ( !cnt )

                .if ( [rbx].token != T_FINAL )

                    mov rdx,[rbx+asm_tok].tokpos
                    .if ( [rdi].flags & S_ISSTATIC )
                        mov rdx,[rbx+asm_tok*2].tokpos
                    .endif
                    tstrcat( p, rdx )
                .endif

            .elseif ( [rdx].proc_info.flags & PROC_HAS_VARARG )

                mov rdx,[rbx+asm_tok].tokpos
                .if ( [rbx+asm_tok].tokval == T_ADDR && [rdi].flags & S_METHOD )
                    mov rdx,[rbx+asm_tok*2].tokpos
                .endif
                tstrcat( p, rdx )
           .else
                mov esi,1
                mov rdx,args[0]
                .if ( [rdi].flags & S_ISSTATIC )
                    mov rdx,[rbx+asm_tok*2].string_ptr
                    xor esi,esi
                .endif
                tstrcat( p, rdx )
                .for ( : esi < cnt: esi++ )
                    tstrcat( p, ", " )
                    .if ( args[rsi*string_t] )
                        tstrcat( p, args[rsi*string_t] )
                    .endif
                .endf
                mov rsi,sym
            .endif
            tstrcat( p, ")" )

        .endif

        .if struct_ptr
ifndef ASMC64
            mov edi,T_EAX
            .if ( ModuleInfo.Ofssize == USE64 )
endif
                mov edi,T_RAX
                .if ( [rsi].langtype == LANG_SYSCALL )
                    mov edi,T_R10
                .endif
ifndef ASMC64
            .endif
endif
            mov rbx,struct_ptr
            mov rcx,SymSearch( [rbx].string_ptr )
            AssignPointer( rcx, edi, struct_ptr, pclass, [rsi].langtype, pmacro)
ifndef ASMC64

            ; v2.34.64 - indirection for 32-bit C/STDCALL -- indirect32_3.asm

            .if ( edi == T_EAX && ( [rsi].langtype == LANG_C || [rsi].langtype == LANG_STDCALL ) )

                ; *this is the last push and EAX is the interface...

                .if ( rax )
                    .if ( [rax].asym.mem_type == MT_TYPE )
                        mov rax,[rax].asym.type
                    .endif
                    .if ( [rax].asym.mem_type == MT_PTR )
                        mov rax,[rax].asym.target_type
                    .endif
                    .if ( rax && !( [rax].asym.flags & S_VTABLE ) )
                        xor eax,eax
                    .endif
                .endif
                .if ( rax )
                    AddLineQueue( " mov [esp], eax\n mov eax, [eax]" )
                .endif
            .endif
endif
        .elseif ( !pmacro )

            imul ebx,parmpos,asm_tok
            add rbx,tokenarray

            .if ( ModuleInfo.Ofssize == USE64 )

                .if ( [rsi].langtype == LANG_SYSCALL )
                    AddLineQueue( " mov r10, [rdi]" )
                .else
                    AddLineQueue( " mov rax, [rcx]" )
                .endif
ifndef ASMC64
            .elseif ( ModuleInfo.Ofssize == USE32 )

                .new reg:int_t = T_EAX ; v2.31 - skip mov eax,reg

                .if ( [rsi].langtype == LANG_WATCALL || [rsi].langtype == LANG_ASMCALL )

                    ; do nothing: class in eax

                .elseif ( [rsi].langtype == LANG_FASTCALL )

                    ; class in ecx

                    mov reg,T_ECX

                .elseif ( [rbx+asm_tok].tokval != T_EAX )

                    .if ( [rbx+asm_tok].token == T_REG && [rbx+asm_tok].tokval > T_EAX &&
                          [rbx+asm_tok].tokval <= T_EDI )
                        mov reg,[rbx+asm_tok].tokval
                    .elseif ( [rbx+asm_tok].token == T_RES_ID && [rbx+asm_tok].tokval == T_ADDR )
                        AddLineQueueX( " lea eax, %s", [rbx+asm_tok*2].string_ptr )
                    .else
                        AddLineQueueX( " mov eax, %s", [rbx+asm_tok].string_ptr )
                    .endif
                .endif
                AddLineQueueX( " mov eax, [%r]", reg )
endif
            .endif
        .endif
    .endif

    mov rbx,tokenarray
    imul edx,parmpos,asm_tok
    imul ecx,namepos,asm_tok

    .if ( pmacro == NULL )

        mov rax,[rbx+rdx].tokpos
        sub rax,[rbx+rcx].tokpos
        mov size,eax

        tmemcpy( p, [rbx+rcx].tokpos, size )

        mov edx,size
        mov byte ptr [rax+rdx],0
    .endif

    AddLineQueue( StringBufferEnd )

    mov rdi,info
    mov rsi,sym

    assume rdi:ptr proc_info

    .if ( ( [rsi].langtype == LANG_C || ( [rsi].langtype == LANG_SYSCALL && !fastcall_id ) ) &&
          ( [rdi].parasize || ( [rdi].flags & PROC_HAS_VARARG && size_vararg ) ) )

        ; v2.17: if stackbase is active, use the ofssize of the assumed SS;
        ; however, do this in 16-bit code only ( don't generate "add SP, x" in 32-bit )

        movzx eax,ModuleInfo.Ofssize
        .if ( ModuleInfo.Ofssize == USE16 && ModuleInfo.StackBase )
            GetOfssizeAssume( ASSUME_SS )
        .endif
        lea rdx,stackreg
        mov eax,[rdx+rax*4]

        .if ( [rdi].flags & PROC_HAS_VARARG )

            mov ecx,[rdi].parasize
            add ecx,size_vararg

            AddLineQueueX( " add %r, %u", eax, ecx )
        .else
            AddLineQueueX( " add %r, %u", eax, [rdi].parasize )
        .endif

    .elseif ( fastcall_id )

        fast_fcend( pproc, numParam, value )
    .endif

    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL )
    RunLineQueue()

    mov rcx,pmacro
    .if ( rcx && [rcx].asym.altname )

        mov rdx,[rcx].asym.altname
        mov [rdx],rsi
    .endif
    .return( NOT_ERROR )

InvokeDirective endp

    end
