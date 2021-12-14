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
include Indirection.inc
include fastpass.inc

QueueTestLines  proto :string_t
ExpandHllProc   proto :string_t, :int_t, :ptr asm_tok
GetSegmentPart  proto :ptr expr, :string_t, :string_t
fastcall_init   proto
GetFastcallId   proto :int_t
get_regname     proto :int_t, :int_t

define NUMQUAL

.enum reg_used_flags {
    R0_USED       = 0x01, ;; register contents of AX/EAX/RAX is destroyed
    R0_H_CLEARED  = 0x02, ;; 16bit: high byte of R0 (=AH) has been set to 0
    R0_X_CLEARED  = 0x04, ;; 16bit: register R0 (=AX) has been set to 0
    R2_USED       = 0x08, ;; contents of DX is destroyed ( via CWD ); cpu < 80386 only
    }

fastcall_conv   struct
invokestart     proc :ptr dsym, :int_t, :int_t, :ptr asm_tok, :ptr int_t
invokeend       proc :ptr dsym, :int_t, :int_t
handleparam     proc :ptr dsym, :int_t, :ptr dsym, :int_t, :ptr expr, :string_t, :ptr uint_8
fastcall_conv   ends

externdef       fastcall_tab:fastcall_conv
public          size_vararg

.data

size_vararg     int_t 0 ;; size of :VARARG arguments

regax           uint_t T_AX, T_EAX, T_RAX
win64regs       uint_8 T_RCX, T_RDX, T_R8, T_R9
elf64regs       uint_8 T_RDI, T_RSI, T_RDX, T_RCX, T_R8, T_R9

    .code

    assume ebx:ptr asm_tok
    B equ <byte ptr>

SkipTypecast proc private uses esi edi ebx fullparam:string_t, i:int_t, tokenarray:ptr asm_tok

    mov  edi,fullparam
    imul ebx,i,asm_tok
    add  ebx,tokenarray
    xor  eax,eax
    mov  B[edi],al

    .for ( : : ebx += asm_tok )

        .break .if (( [ebx].token == T_COMMA ) || ( [ebx].token == T_FINAL ) )
        .if (( [ebx+16].token == T_BINARY_OPERATOR ) && ( [ebx+16].tokval == T_PTR ) )
            add ebx,16
        .else
            mov esi,[ebx].tokpos
            mov ecx,[ebx+16].tokpos
            sub ecx,esi
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

PushInvokeParam proc private uses esi edi ebx i:int_t, tokenarray:ptr asm_tok, pproc:ptr dsym,
        curr:ptr dsym, reqParam:int_t, r0flags:ptr uint_8

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
    add  ebx,tokenarray

    .for ( ecx = 0 : ecx <= reqParam : )

        .return(ERROR) .if ( [ebx].token == T_FINAL ) ;; this is no real error!

        .if ( [ebx].token == T_COMMA )
            inc ecx
        .endif
        add ebx,16
        inc i
    .endf
    mov currParm,ecx

    ;; if curr is NULL this call is just a parameter check

    mov edi,curr
    .return( NOT_ERROR ) .if ( !edi )

    movzx ecx,ModuleInfo.Ofssize
    mov eax,regax[ecx*4]
    mov t_regax,eax

    mov eax,reqParam
    inc eax
    mov ParamId,eax

    mov eax,ModuleInfo.curr_cpu
    and eax,P_CPU_MASK
    mov curr_cpu,eax

    mov esi,pproc
    mov fastcall_id,GetFastcallId( [esi].asym.langtype )
    mov r_ax,T_EAX
    mov t_addr,FALSE

    mov psize,[edi].asym.total_size

    ;; ADDR: the argument's address is to be pushed?

    .if ( [ebx].token == T_RES_ID && [ebx].tokval == T_ADDR )
        mov t_addr,TRUE
        .if ( [edi].asym.mem_type != MT_ABS )
            add ebx,16
            inc i
        .endif
    .endif

    ;; copy the parameter tokens to fullparam

    .for ( edx = ebx: [edx].asm_tok.token != T_COMMA && [edx].asm_tok.token != T_FINAL: edx+=16 )
    .endf

    mov esi,[ebx].tokpos
    mov ecx,[edx].asm_tok.tokpos
    sub ecx,esi
    lea edi,fullparam
    rep movsb
    mov B[edi],0

    mov edi,curr
    .if ( [edi].asym.mem_type == MT_ABS && t_addr )
        add ebx,16
        inc i
    .endif

    mov j,i
    mov esi,pproc

    ;; v2.11: GetSymOfssize() doesn't work for state SYM_TYPE

    movzx eax,[esi].asym.segoffsize
    .if [esi].asym.state != SYM_TYPE
        GetSymOfssize(esi)
    .endif
    mov Ofssize,al
    mov ecx,eax
    mov eax,2
    shl eax,cl
    add eax,2
    mov fptrsize,eax

    .if ( t_addr )

        ;; v2.06: don't handle forward refs if -Zne is set

        .return .if ( EvalOperand( &j, tokenarray, Token_Count, &opnd, ModuleInfo.invoke_exprparm ) == ERROR )

        imul ebx,j,asm_tok
        add  ebx,tokenarray

        ;; DWORD (16bit) and FWORD(32bit) are treated like FAR ptrs
        ;; v2.11: argument may be a FAR32 pointer ( psize == 6 ), while
        ;; fptrsize may be just 4!

        .if ( psize > fptrsize && fptrsize > 4 )

            ;; QWORD is NOT accepted as a FAR ptr
            asmerr(2114, ParamId)
            .return(NOT_ERROR)
        .endif

        .if ( fastcall_id  )
            mov eax,fastcall_id
            dec eax
            imul ecx,eax,fastcall_conv
            .if ( fastcall_tab[ecx].handleparam( pproc,
                reqParam, curr, t_addr, &opnd, &fullparam, r0flags ) )
                .return( NOT_ERROR )
            .endif
        .endif

        .if ( opnd.kind == EXPR_REG || opnd.flags & E_INDIRECT )

ifndef __ASMC64__

            .if ( [edi].asym.is_far || psize == fptrsize )
                mov ecx,opnd.sym
                .if ( ecx && [ecx].asym.state == SYM_STACK )
                    AddLineQueue( " push ss" )
                .elseif ( opnd.override != NULL )
                    mov ecx,opnd.override
                    AddLineQueueX( " push %s", [ecx].asm_tok.string_ptr )
                .else
                    AddLineQueue( " push ds" )
                .endif
            .endif
endif
            AddLineQueueX( " lea %r, %s", t_regax, &fullparam )
            mov ecx,r0flags
            or B[ecx],R0_USED
            AddLineQueueX( " push %r", t_regax )

        .else
         push_address:

            ;; push segment part of address?
            ;; v2.11: do not assume a far pointer if psize == fptrsize
            ;; ( parameter might be near32 in a 16-bit environment )

ifndef __ASMC64__

            mov cl,[edi].asym.Ofssize
            mov eax,2
            shl eax,cl

            .if ( [edi].asym.is_far || psize > eax )

                GetSegmentPart( &opnd, &buffer, &fullparam )
                .if ( eax )

                    ;; v2.11: push segment part as WORD or DWORD depending on target's offset size
                    ;; problem: "pushw ds" is not accepted, so just emit a size prefix.

                    push eax
                    .if ( Ofssize != ModuleInfo.Ofssize || ( [edi].asym.Ofssize == USE16 && CurrWordSize > 2 ) )

                        AddLineQueue( " db 66h" )
                    .endif
                    pop eax
                    AddLineQueueX( " push %r", eax )
                .else
                    AddLineQueueX( " push %s", &buffer )
                .endif
            .endif

            ;; push offset part of address

            .if curr_cpu < P_186

                AddLineQueueX( " mov ax, offset %s", &fullparam )
                AddLineQueue( " push ax" )
                mov ecx,r0flags
                or B[ecx],R0_USED

            .else

                .if ( [edi].asym.sflags & S_ISVARARG && opnd.Ofssize == USE_EMPTY && opnd.sym )

                    mov opnd.Ofssize,GetSymOfssize( opnd.sym )
                .endif

                ;; v2.04: expand 16-bit offset to 32
                ;; v2.11: also expand if there's an explicit near32 ptr requested in 16-bit


                .if ( ( opnd.Ofssize == USE16 && CurrWordSize > 2 ) || \
                    ( [edi].asym.Ofssize == USE32 && CurrWordSize == 2 ) )
                    AddLineQueueX( " pushd offset %s", &fullparam )
                .elseif ( CurrWordSize > 2 && [edi].asym.Ofssize == USE16 && \
                        ( [edi].asym.is_far || Ofssize == USE16 ) ) ;; v2.11: added
                    AddLineQueueX( " pushw offset %s", &fullparam )
                .else
                    .if ( !( [esi].asym.flag2 & S_ISINLINE && [edi].asym.sflags & S_ISVARARG ) )
                        AddLineQueueX( " push offset %s", &fullparam )
                        ;; v2.04: a 32bit offset pushed in 16-bit code
                        .if ( [edi].asym.sflags & S_ISVARARG && CurrWordSize == 2 && opnd.Ofssize > USE16 )
                            add size_vararg,CurrWordSize
                        .endif
                    .endif
                .endif
            .endif
endif
        .endif

        .if ( [edi].asym.sflags & S_ISVARARG )
            movzx eax,CurrWordSize
            .if ( [edi].asym.is_far )
                add eax,eax
            .endif
            add size_vararg,eax
        .endif

        .return( NOT_ERROR )
    .endif

    ;; ! ADDR branch

    ;; handle the <reg>::<reg> case here, the evaluator wont handle it

    .if ( [ebx].token == T_REG && [ebx+16].token == T_DBL_COLON && [ebx+32].token == T_REG )

        .new asize2:int_t

        ;; for pointers, segreg size is assumed to be always 2

ifndef __ASMC64__

        .if ( GetValueSp( [ebx].tokval ) & OP_SR )

            mov asize2,2

            ;; v2.11: if target and current src have different offset sizes,
            ;; the push of the segment register must be 66h-prefixed!

            .if ( Ofssize != ModuleInfo.Ofssize || ( [edi].asym.Ofssize == USE16 && CurrWordSize > 2 ) )

                AddLineQueue( " db 66h" )
            .endif
        .else
endif
            mov asize2,SizeFromRegister( [ebx].tokval )
ifndef __ASMC64__
        .endif
endif

        mov asize,SizeFromRegister( [ebx+32].tokval )

        ;; v2.31.35: Watcom handles the two first sets

        .if ( asize2 != 8 && !( fastcall_id == FCT_WATCOMC + 1 && currParm < 3 ) )

            AddLineQueueX( " push %r", [ebx].tokval )
        .endif

        ;; v2.04: changed

        mov eax,asize
        add eax,asize2
        .if ( ( [edi].asym.sflags & S_ISVARARG ) && al != CurrWordSize )
            add size_vararg,asize2
        .else
            add asize,asize2
        .endif
        strcpy( &fullparam, [ebx+32].string_ptr )

        mov opnd.kind,EXPR_REG
        and opnd.flags,not E_INDIRECT
        mov opnd.sym,NULL
        .if ( asize2 != 8 )
            mov opnd.base_reg,&[ebx+32] ;; for error msg 'eax overwritten...'
        .else
            mov opnd.base_reg,ebx
        .endif

    .else

        ;; v2.06: don't handle forward refs if -Zne is set
        ;; v2.31: :ABS to const

        .if ( [edi].asym.mem_type == MT_ABS )

            mov opnd.kind,EXPR_CONST
            mov opnd.mem_type,MT_ABS
            mov opnd.mbr,NULL
            mov opnd.base_reg,NULL

        .else

            .return .if EvalOperand( &j, tokenarray, Token_Count, &opnd,
                            ModuleInfo.invoke_exprparm ) == ERROR

            imul ebx,j,asm_tok
            add  ebx,tokenarray
        .endif

        ;; for a simple register, get its size

        .if ( opnd.kind == EXPR_REG && !( opnd.flags & E_INDIRECT ) )

            mov ecx,opnd.base_reg
            mov asize,SizeFromRegister([ecx].asm_tok.tokval)

        .elseif ( opnd.kind == EXPR_CONST || opnd.mem_type == MT_EMPTY )

            mov asize,psize

            ;; v2.04: added, to catch 0-size params ( STRUCT without members )

            .if ( psize == 0 )

                .if !( [edi].asym.sflags & S_ISVARARG )

                    asmerr( 2114, ParamId )
                .endif

                ;; v2.07: for VARARG, get the member's size if it is a structured var

                mov ecx,opnd.mbr
                .if ( ecx && [ecx].asym.mem_type == MT_TYPE )
                    mov asize,SizeFromMemtype( [ecx].asym.mem_type, opnd.Ofssize, [ecx].asym.type )
                .endif
            .endif

        .elseif ( opnd.mem_type != MT_TYPE )

            .if ( opnd.kind == EXPR_ADDR && !( opnd.flags & E_INDIRECT ) && opnd.sym && \
                     opnd.inst == EMPTY && ( opnd.mem_type == MT_NEAR || opnd.mem_type == MT_FAR ) )

                jmp push_address
            .endif

            .if ( opnd.Ofssize == USE_EMPTY )

                mov opnd.Ofssize,ModuleInfo.Ofssize
            .endif

            mov asize,SizeFromMemtype( opnd.mem_type, opnd.Ofssize, opnd.type )
        .else

            mov ecx,opnd.sym
            .if !ecx

                mov ecx,opnd.mbr
            .endif
            mov ecx,[ecx].asym.type
            mov asize,[ecx].asym.total_size
        .endif
    .endif

    movzx eax,CurrWordSize
    mov pushsize,eax

    .if ( [edi].asym.sflags & S_ISVARARG )

        mov psize,asize
    .endif

    .if ( asize == 16 && opnd.mem_type == MT_REAL16 && pushsize == 4 )

        mov asize,psize
    .endif

    .if ( fastcall_id )

        mov eax,fastcall_id
        dec eax
        imul ecx,eax,fastcall_conv

        .if ( fastcall_tab[ecx].handleparam( pproc, reqParam, curr, t_addr, &opnd, &fullparam, r0flags ) )

            .return( NOT_ERROR )
        .endif
    .endif

    .if ( ( asize > psize ) || ( asize < psize && [edi].asym.mem_type == MT_PTR ) )

        asmerr( 2114, ParamId )
        .return( NOT_ERROR )
    .endif

    .if ( pushsize == 8 )

        mov r_ax,T_RAX
    .endif

    .if ( ( opnd.kind == EXPR_ADDR && opnd.inst != T_OFFSET ) || \
          ( opnd.kind == EXPR_REG && opnd.flags & E_INDIRECT ) )

        ;; catch the case when EAX has been used for ADDR,
        ;; and is later used as addressing register!

        mov ecx,r0flags
        mov edx,opnd.base_reg
        mov eax,opnd.idx_reg

        .if ( B[ecx] && ( ( edx != NULL && \
            ( [edx].asm_tok.tokval == T_EAX || [edx].asm_tok.tokval == T_RAX ) ) || \
            ( eax != NULL && \
            ( [eax].asm_tok.tokval == T_EAX || [eax].asm_tok.tokval == T_RAX ) ) ) )

            mov B[ecx],0
            asmerr( 2133 )
        .endif

        .if ( [edi].asym.sflags & S_ISVARARG )

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

            ;; in params like "qword ptr [eax]" the typecast
            ;; has to be removed

            .if ( opnd.flags & E_EXPLICIT )

                SkipTypecast( &fullparam, i, tokenarray )
                and opnd.flags,not E_EXPLICIT
            .endif

ifndef __ASMC64__

            .while ( asize > 0 )

                .if ( asize & 2 )

                    ;; ensure the stack remains dword-aligned in 32bit

                    .if ( ModuleInfo.Ofssize > USE16 )

                        ;; v2.05: better push a 0 word?
                        ;; ASMC v1.12: ensure the stack remains dword-aligned in 32bit

                        .if (pushsize == 4)

                            add size_vararg,2
                        .endif
                        movzx ecx,ModuleInfo.Ofssize
                        AddLineQueueX( " sub %r, 2", stackreg[ecx*4] )
                    .endif

                    sub asize,2
                    AddLineQueueX( " push word ptr %s+%u", &fullparam, asize )

                .else

                    ;; v2.23 if stack base is ESP

                    movzx ecx,ModuleInfo.Ofssize
                    mov ecx,ModuleInfo.basereg[ecx*4]
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

            ;; v2.11: added, use MOVSX/MOVZX if cpu >= 80386

            .if ( asize < 4 && psize > 2 && IS_SIGNED(opnd.mem_type) && curr_cpu >= P_386 )

                AddLineQueueX( " movsx eax, %s", &fullparam )
                AddLineQueueX( " push %r", r_ax )

                mov ecx,r0flags
                mov B[ecx],R0_USED ;; reset R0_H_CLEARED

            .else

                .switch ( opnd.mem_type )
                .case MT_BYTE
                .case MT_SBYTE

                    .if ( psize == 1 && !( [edi].asym.sflags & S_ISVARARG ) )

                        AddLineQueueX( " mov al, %s", &fullparam )
                        AddLineQueueX( " push %r", t_regax )
ifndef __ASMC64__
                    .elseif ( pushsize == 2 ) ;; 16-bit code?

                        .if ( opnd.mem_type == MT_BYTE )

                            .if ( psize == 4 )

                                .if ( curr_cpu < P_186 )

                                    mov ecx,r0flags
                                    .if ( !( B[ecx] & R0_X_CLEARED ) )
                                        AddLineQueue( " xor ax, ax" )
                                    .endif
                                    mov ecx,r0flags
                                    or B[ecx],( R0_X_CLEARED or R0_H_CLEARED )
                                    AddLineQueue( " push ax" )
                                .else
                                    AddLineQueue( " push 0" )
                                .endif
                            .endif

                            AddLineQueueX( " mov al, %s", &fullparam )
                            mov ecx,r0flags
                            .if ( !( B[ecx] & R0_H_CLEARED ))

                                or B[ecx],R0_H_CLEARED
                                AddLineQueue( " mov ah, 0" )
                            .endif

                        .else

                            AddLineQueueX( " mov al, %s", &fullparam )

                            mov ecx,r0flags
                            mov B[ecx],0 ;; reset AH_CLEARED
                            AddLineQueue( " cbw" )

                            .if ( psize == 4 )

                                AddLineQueue( "cwd" )
                                AddLineQueue( " push dx" )
                                mov ecx,r0flags
                                or B[ecx],R2_USED
                            .endif
                        .endif
                        AddLineQueue( " push ax" )
endif
                    .else

                        mov ecx,T_MOVSX
                        .if opnd.mem_type == MT_BYTE

                            mov ecx,T_MOVZX
                        .endif
                        AddLineQueueX( " %r eax, %s", ecx, &fullparam )
                        AddLineQueueX( " push %r", r_ax )
                    .endif

                    mov ecx,r0flags
                    or B[ecx],R0_USED
                    .endc

                .case MT_WORD
                .case MT_SWORD

                    .if ( opnd.mem_type == MT_WORD && ( Options.masm_compat_gencode || psize == 2 ))

                        .if ( pushsize == 8 )

                            AddLineQueueX(" mov ax, %s", &fullparam )
                            AddLineQueue(" push rax" )
                            mov ecx,r0flags
                            mov B[ecx],R0_USED ;; reset R0_H_CLEARED
ifndef __ASMC64__
                        .else
                            .if ( [edi].asym.sflags & S_ISVARARG || psize != 2 )

                                AddLineQueue( " pushw 0" )
                            .else

                                movzx ecx,ModuleInfo.Ofssize
                                AddLineQueueX( " sub %r, 2", stackreg[ecx*4] )
                            .endif
                            AddLineQueueX( " push %s", &fullparam )
endif
                        .endif
                    .else

                        mov ecx,T_MOVSX
                        .if opnd.mem_type == MT_WORD

                            mov ecx,T_MOVZX
                        .endif
                        AddLineQueueX( " %r eax, %s", ecx, &fullparam )
                        AddLineQueueX( " push %r", r_ax )
                        mov ecx,r0flags
                        or B[ecx],R0_USED
                    .endif
                    .endc

                .case MT_DWORD
                .case MT_SDWORD

                    .if ( pushsize == 8 )

                        AddLineQueueX( " mov eax, %s", &fullparam )
                        AddLineQueue ( " push rax" )
                        mov ecx,r0flags
                        or B[ecx],R0_USED
                        .endc
                    .endif

                .default

                    .if ( asize == 3 ) ;; added v2.29

                        .if ( pushsize > 2 )

                            AddLineQueueX( " mov al, byte ptr %s[2]", &fullparam )
                            AddLineQueue ( " shl eax, 16" )
                            AddLineQueueX( " mov ax, word ptr %s", &fullparam )
                            AddLineQueueX( " push %r", r_ax )
                        .else
                            AddLineQueueX( " push word ptr %s[2]", &fullparam )
                            AddLineQueueX( " push word ptr %s", &fullparam )
                        .endif
                    .else

                        AddLineQueueX( " push %s", &fullparam )
                    .endif
                .endsw
            .endif

        .else ;; asize == pushsize

            .if ( IS_SIGNED(opnd.mem_type) && psize > asize )

                .if ( psize > 2 && ( curr_cpu >= P_386 ) )

                    AddLineQueueX( " movsx eax, %s", &fullparam )
                    AddLineQueueX( " push %r", r_ax )
                    mov ecx,r0flags
                    mov B[ecx],R0_USED ;; reset R0_H_CLEARED
ifndef __ASMC64__
                .elseif ( pushsize == 2 && psize > 2 )

                    AddLineQueueX( " mov ax, %s", &fullparam )
                    AddLineQueue ( " cwd" )
                    AddLineQueue ( " push dx" )
                    AddLineQueue ( " push ax" )
                    mov ecx,r0flags
                    mov B[ecx],R0_USED or R2_USED
endif
                .else
                    AddLineQueueX( " push %s", &fullparam )
                .endif
            .else
ifndef __ASMC64__
                .if ( pushsize == 2 && psize > 2 )

                    .if ( curr_cpu < P_186 )

                        mov ecx,r0flags
                        .if ( !( B[ecx] & R0_X_CLEARED ) )

                            AddLineQueue( " xor ax, ax" )
                        .endif
                        AddLineQueue( " push ax" )
                        mov ecx,r0flags
                        or B[ecx],( R0_USED or R0_X_CLEARED or R0_H_CLEARED )
                    .else
                        AddLineQueue( " pushw 0" )
                    .endif
                .endif
endif
                AddLineQueueX( " push %s", &fullparam )
            .endif
        .endif

    .else  ;; the parameter is a register or constant value!

        .if ( opnd.kind == EXPR_REG )

           .new reg:int_t
            mov ecx,opnd.base_reg
            mov eax,[ecx].asm_tok.tokval
            mov reg,eax

           .new optype:dword = GetValueSp(eax)

            ;; v2.11
            .if ( [edi].asym.sflags & S_ISVARARG && psize < pushsize )

                mov psize,pushsize
            .endif

            ;; v2.06: check if register is valid to be pushed.
            ;; ST(n), MMn, XMMn, YMMn and special registers are NOT valid!

            .if ( optype & ( OP_STI or OP_MMX or OP_XMM or OP_YMM or OP_ZMM or OP_RSPEC ) )

                .return( asmerr( 2114, ParamId ) )
            .endif

            mov ecx,r0flags
            .if ( ( B[ecx] & R0_USED ) && ( reg == T_AH || ( optype & OP_A ) ) )

                and B[ecx],not R0_USED
                asmerr( 2133 )

            .elseif ( ( B[ecx] & R2_USED ) && ( reg == T_DH || GetRegNo(reg) == 2 ) )

                and B[ecx],not R2_USED
                asmerr( 2133 )
            .endif

            mov edx,2
            mov cl,Ofssize
            shl edx,cl
            .if ( asize != psize || asize < edx )

                ;; register size doesn't match the needed parameter size.

                .if ( psize > 4 && pushsize < 8 )

                    asmerr( 2114, ParamId )
                .endif

                .if ( asize <= 2 && ( psize == 4 || pushsize == 4 ) )

                    .if ( curr_cpu >= P_386 && asize == psize )

                        .if ( asize == 2 )

                            sub reg,T_AX
                            add reg,T_EAX
                        .else

                            ;; v2.11: hibyte registers AH, BH, CH, DH
                            ;; ( no 4-7 ) needs special handling

                            .if ( reg < T_AH )

                                sub reg,T_AL
                                add reg,T_EAX
                            .else

                                AddLineQueueX( " mov al, %s", &fullparam )
                                mov ecx,r0flags
                                or B[ecx],R0_USED
                                mov reg,T_EAX
                            .endif
                            mov asize,2
                        .endif
ifndef __ASMC64__
                    .elseif ( IS_SIGNED( opnd.mem_type ) && pushsize < 4 )

                        ;; psize is 4 in this branch

                        .if ( curr_cpu >= P_386 )

                            AddLineQueueX( " movsx eax, %s", &fullparam )
                            mov ecx,r0flags
                            mov B[ecx],R0_USED
                            mov reg,T_EAX

                        .else

                            mov ecx,r0flags
                            mov B[ecx],R0_USED or R2_USED
                            .if ( asize == 1 )

                                .if ( reg != T_AL )

                                    AddLineQueueX( " mov al, %s", &fullparam )
                                .endif
                                AddLineQueue( " cbw" )
                            .elseif ( reg != T_AX )

                                AddLineQueueX( " mov ax, %s", &fullparam )
                            .endif
                            AddLineQueue( " cwd" )
                            AddLineQueue( " push dx" )
                            mov reg,T_AX

                        .endif
                        mov asize,2 ;; done

                    .elseif ( curr_cpu >= P_186 )

                        .if ( pushsize == 4 )

                            .if ( asize == 1 )

                                ;; handled below

                            .elseif ( psize <= 2 )

                                movzx ecx,ModuleInfo.Ofssize
                                AddLineQueueX( " sub %r, 2", stackreg[ecx*4] )

                            .elseif ( IS_SIGNED( opnd.mem_type ) )

                                AddLineQueueX( " movsx eax, %s", &fullparam )
                                mov ecx,r0flags
                                mov B[ecx],R0_USED
                                mov reg,T_EAX
                            .else
                                AddLineQueue( " pushw 0" )
                            .endif
                        .else
                            AddLineQueue( " pushw 0" )
                        .endif

                    .else

                        mov ecx,r0flags
                        .if ( !( B[ecx] & R0_X_CLEARED ) )

                            ;; v2.11: extra check needed

                            .if ( reg == T_AH || ( optype & OP_A ) )

                                asmerr( 2133 )
                            .endif
                            AddLineQueue( " xor ax, ax" )
                        .endif

                        AddLineQueue( " push ax" )
                        mov ecx,r0flags
                        mov B[ecx],R0_USED or R0_H_CLEARED or R0_X_CLEARED
endif
                    .endif

                .elseif ( pushsize == 8 && ( ( asize == psize && psize < 8 ) || \
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

                            ;; v2.10: consider signed type coercion!

                            mov eax,R0_USED or R0_H_CLEARED
                            mov ecx,T_MOVZX
                            .if IS_SIGNED(opnd.mem_type)

                                mov ecx,T_MOVSX
                                mov eax,R0_USED
                            .endif

                            mov edx,r0flags
                            mov [edx],al
                            AddLineQueueX( " %r %r, %s", ecx, t_regax, &fullparam )

                        .else

                            .if ( eax != T_AL )

                                AddLineQueueX( " mov al, %s", &fullparam )

                                mov ecx,r0flags
                                or  B[ecx],R0_USED
                                and B[ecx],not R0_X_CLEARED
                            .endif

                            .if ( psize != 1 ) ;; v2.11: don't modify AH if paramsize is 1

                                mov ecx,r0flags
                                .if ( IS_SIGNED( opnd.mem_type ) )

                                    and B[ecx],not ( R0_H_CLEARED or R0_X_CLEARED )
                                    AddLineQueue( " cbw" )

                                .elseif ( !( B[ecx] & R0_H_CLEARED ) )

                                    or B[ecx],R0_H_CLEARED
                                    AddLineQueue( " mov ah, 0" )
                                .endif
                            .endif
                        .endif
                        mov reg,t_regax

                    .else

                        ;; convert 8-bit to 16/32-bit register name

                        .if ( ( curr_cpu >= P_386) && ( psize == 4 || pushsize == 4 ) )

                            sub eax,T_AL
                            add eax,T_EAX

                        .elseif ( pushsize < 8 )

                            sub eax,T_AL
                            add eax,T_AX
                        .endif
                        mov reg,eax
                    .endif
                .endif
            .endif

            AddLineQueueX( " push %r", reg )

            ;; v2.05: don't change psize if > pushsize

            .if ( psize < pushsize )

                ;; v2.04: adjust psize ( for siz_vararg update )

                mov psize,pushsize
            .endif

        .else ;; constant value

            ;; v2.06: size check

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

            .if ( psize < eax ) ;; ensure that the default argsize (2,4,8) is met

                .if ( psize == 0 && [edi].asym.sflags & S_ISVARARG )

                    ;; v2.04: push a dword constant in 16-bit

                    .if ( eax == 2 && \
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
ifndef __ASMC64p__
                mov ecx,r0flags
                or B[ecx],R0_USED

                .switch ( psize )
                .case 2
                    .if ( opnd.value != 0 || opnd.kind == EXPR_ADDR )

                        AddLineQueueX( " mov ax, %s", &fullparam )
                    .else
                        .if ( !( B[ecx] & R0_X_CLEARED ) )

                            AddLineQueue( " xor ax, ax" )
                        .endif

                        mov ecx,r0flags
                        or B[ecx],R0_H_CLEARED or R0_X_CLEARED
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
                        mov ecx,r0flags
                        or B[ecx],R0_H_CLEARED or R0_X_CLEARED
                    .endif
                    .endc
                .default
                    asmerr( 2114, ParamId )
                .endsw
                AddLineQueue( " push ax" )
endif
            .else ;; cpu >= 80186

                mov ebx,T_PUSH
                mov esi,EMPTY

                .if ( psize != pushsize )

                    .switch psize
                    .case 2

                        mov ebx,T_PUSHW
                        .endc

                    .case 6 ;; v2.04: added

                        ;; v2.11: use pushw only for 16-bit target
ifndef __ASMC64__
                        .if ( Ofssize == USE16 )

                            mov ebx,T_PUSHW
                        .elseif ( Ofssize == USE32 && CurrWordSize == 2 )

                            mov ebx,T_PUSHD
                        .endif
endif
                        AddLineQueueX( " %r (%s) shr 32t", ebx, &fullparam )

                        ;; no break

                    .case 4
ifndef __ASMC64__
                        .if ( curr_cpu >= P_386 )

                            mov ebx,T_PUSHD
                        .else
                            mov ebx,T_PUSHW
                            AddLineQueueX( " pushw highword (%s)", &fullparam )
                            mov esi,T_LOWWORD
                        .endif
endif
                        .endc

                        ;; v2.25: added support for REAL10 and REAL16

                    .case 10

                        .endc .if ( Ofssize == USE16 || ModuleInfo.strict_masm_compat == TRUE || opnd.kind != EXPR_FLOAT )

                        quad_resize( &opnd, 10)
                        AddLineQueueX( " push 0x%x", opnd.h64_l )

                        .if ( curr_cpu >= P_64 )

                            mov ecx,r0flags
                            or B[ecx],R0_USED
                            AddLineQueueX( " mov rax, 0x%lx", opnd.llvalue )
                            AddLineQueue( " push rax" )
ifndef __ASMC64__
                        .else

                            mov ebx,T_PUSHD
                            AddLineQueueX( " pushd high32 (0x%lx)", opnd.llvalue )
                            AddLineQueueX( " pushd low32 (0x%lx)",  opnd.llvalue )
endif
                        .endif
                        jmp skip_push

                    .case 16

                        .endc .if ( Ofssize == USE16 || ModuleInfo.strict_masm_compat == TRUE )
ifndef __ASMC64__
                        .if Ofssize == USE32

                            mov ebx,T_PUSHD
                            AddLineQueueX( " pushd high32 (0x%lx)", opnd.hlvalue )
                            AddLineQueueX( " pushd low32 (0x%lx)",  opnd.hlvalue )
                            AddLineQueueX( " pushd high32 (0x%lx)", opnd.llvalue )
                            AddLineQueueX( " pushd low32 (0x%lx)",  opnd.llvalue )
                            jmp skip_push
                        .endif
endif
                        .if ( opnd.h64_h == 0 || opnd.h64_h == -1 )

                            AddLineQueueX( " push 0x%lx", opnd.hlvalue )
                        .else

                            mov ecx,r0flags
                            or B[ecx],R0_USED
                            AddLineQueueX( " mov rax, 0x%lx", opnd.hlvalue )
                            AddLineQueue( " push rax" )
                        .endif

                        .if ( opnd.l64_h == 0 || opnd.l64_h == -1 )

                            AddLineQueueX( " push 0x%lx", opnd.llvalue )
                        .else

                            mov ecx,r0flags
                            or B[ecx],R0_USED
                            AddLineQueueX( " mov rax, 0x%lx", opnd.llvalue )
                            AddLineQueue( " push rax" )
                        .endif
                        jmp skip_push

                    .case 8

                        .endc .if ( curr_cpu >= P_64 )
ifndef __ASMC64__
                        ;; v2.06: added support for double constants

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

        .if ( [edi].asym.sflags & S_ISVARARG )

            add size_vararg,psize
        .endif

    .endif
    .return( NOT_ERROR )

PushInvokeParam endp

;; generate a call for a prototyped procedure

InvokeDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local sym:ptr asym
  local pproc:ptr dsym
  local arg:ptr dsym
  local p:string_t
  local q:string_t
  local numParam:int_t
  local value:int_t
  local size:int_t
  local parmpos:int_t
  local namepos:int_t
  local porder:int_t
  local j:int_t
  local r0flags:uint_8
  local info:ptr proc_info
  local curr:ptr dsym
  local opnd:expr
  local buffer[MAX_LINE_LEN]:char_t
  local fastcall_id:int_t
  local pmacro:ptr asym
  local pclass:ptr asym
  local struct_ptr:ptr asm_tok

    mov r0flags,0
    mov struct_ptr,NULL
    mov pmacro,NULL

    inc i ;; skip INVOKE directive
    mov namepos,i

    .if ( ModuleInfo.strict_masm_compat == 0 )
        .while 1
            .return .if ( ExpandHllProc( &buffer, i, tokenarray ) == ERROR )
            .break  .if !buffer

            QueueTestLines( &buffer )
            RunLineQueue()
            mov ebx,tokenarray
            .if ( [ebx].tokval == T_INVOKE && [ebx+16].token == T_REG && Token_Count == 2 )
                .return NOT_ERROR
            .endif
        .endw
    .endif

    imul ebx,i,asm_tok
    add ebx,tokenarray

    assume esi:ptr asym

    ;; if there is more than just an ID item describing the invoke target,
    ;; use the expression evaluator to get it

    .if ( [ebx].token != T_ID || ( [ebx+16].token != T_COMMA && [ebx+16].token != T_FINAL ) )

        .return .if EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR

        mov esi,opnd.type
        .if ( esi != NULL && [esi].state == SYM_TYPE )
            mov sym,esi
            mov pproc,esi
            .if ( [esi].mem_type == MT_PROC ) ;; added for v1.95
                jmp isfnproto
            .endif
            .if ( [esi].mem_type == MT_PTR ) ;; v2.09: mem_type must be MT_PTR
                jmp isfnptr
            .endif
        .endif
        .if ( opnd.kind == EXPR_REG )
            mov ebx,opnd.base_reg
            .if ( GetValueSp( [ebx].tokval ) & OP_RGT8 )
                mov sym,GetStdAssume( GetRegNo( [ebx].tokval ) )
            .else
                mov sym,NULL
            .endif
        .else
            mov eax,opnd.mbr
            .if eax == NULL
                mov eax,opnd.sym
            .endif
            mov sym,eax
        .endif

    .else
        mov opnd.base_reg,NULL
        imul ebx,i,asm_tok
        add ebx,tokenarray

        mov sym,SymSearch( [ebx].string_ptr )
        inc i
    .endif

    mov esi,sym
    .if ( esi == NULL )
        ;; v2.04: msg changed
        .return( asmerr( 2190 ) )
    .endif
    mov edx,[esi].type
    mov ecx,[esi].target_type
    .if ( [esi].flag1 & S_ISPROC ) ;; the most simple case: symbol is a PROC
    .elseif ( [esi].mem_type == MT_PTR && ecx && [ecx].asym.flag1 & S_ISPROC )
        mov sym,ecx
    .elseif ( [esi].mem_type == MT_PTR && ecx && [ecx].asym.mem_type == MT_PROC )
        mov pproc,ecx
        jmp isfnproto
    .elseif ( ( [esi].mem_type == MT_TYPE ) && ( [edx].asym.mem_type == MT_PTR || [edx].asym.mem_type == MT_PROC ) )
        ;; second case: symbol is a (function?) pointer
        mov pproc,edx
        .if ( [edx].asym.mem_type != MT_PROC )
            jmp isfnptr
        .endif
    isfnproto:
        ;; pointer target must be a PROTO typedef
        mov esi,pproc
        .if [esi].mem_type != MT_PROC
            .return( asmerr( 2190 ) )
        .endif
    isfnptr:
        ;; get the pointer target
        mov esi,pproc
        mov sym,[esi].target_type
        .if ( eax == NULL )
            .return( asmerr( 2190 ) )
        .endif
    .else
        .return( asmerr( 2190 ) )
    .endif
    mov esi,sym
    mov pproc,esi
    mov ecx,esi
    mov info,[ecx].dsym.procinfo

    .if ( ModuleInfo.strict_masm_compat == 0 )

        imul ebx,namepos,asm_tok
        add ebx,tokenarray
        mov ecx,[esi].target_type
        .if ( [esi].state == SYM_EXTERNAL &&
              ecx && [ecx].asym.state == SYM_MACRO )

            mov eax,[ecx].asym.altname
            .if ( eax )
                mov pmacro,ecx
                mov [eax],ecx
                strcpy( &buffer, [ecx].asym.name )
            .endif

        .elseif ( [ebx].token == T_OP_SQ_BRACKET && \
                  [ebx+3*16].token == T_DOT && opnd.mbr )

            mov edi,opnd.mbr
            .if ( [edi].asym.flag1 & S_METHOD )

                mov pclass,SymSearch( [ebx+4*16].string_ptr )

                .if ( eax && [eax].asym.flag2 & S_ISVTABLE )

                    .if ( [edi].asym.flag2 & S_VMACRO )

                        mov pmacro,[edi].asym.vmacro
                        strcpy( &buffer, [eax].asym.name )
                    .else
                         mov ecx,[eax].asym.class
                        strcat( strcat( strcpy( &buffer, [ecx].asym.name ), "_" ), [edi].asym.name )
                        mov pmacro,SymSearch( eax )
                    .endif

                    mov eax,pmacro
                    .if ( eax && [eax].asym.state == SYM_TMACRO )
                        mov pmacro,SymSearch( [eax].asym.string_ptr )
                    .endif
                    .if ( eax && [eax].asym.state != SYM_MACRO )
                        mov pmacro,NULL
                    .endif

                .endif

                .if ( [edi].asym.flag2 & S_VPARRAY )

                    and [edi].asym.flag2,not S_VPARRAY

                    mov  ecx,Token_Count
                    dec  ecx
                    imul edx,ecx,asm_tok
                    add  edx,tokenarray

                    .while ( edx > ebx )
                        .break .if [edx].asm_tok.token == T_COMMA
                        sub edx,asm_tok
                        dec ecx
                    .endw
                    .if ( [edx].asm_tok.token == T_COMMA )

                        lea eax,[edx+asm_tok]
                        mov struct_ptr,eax
                        mov [edx].asm_tok.token,T_FINAL
                        mov Token_Count,ecx
                    .endif
                .endif
            .endif

            or [esi].flag1,S_METHOD
            .if ( pmacro )
                or [esi].flag2,S_ISINLINE
                .if ( [eax].asym.flag2 & S_ISSTATIC )
                    or [esi].flag2,S_ISSTATIC
                .endif
            .endif
        .endif
    .endif

    mov edx,info
    .for ( ecx = [edx].proc_info.paralist, numParam = 0 : ecx : \
           ecx = [ecx].dsym.nextparam, numParam++ )
    .endf

    mov j,i
    .if ( [esi].flag2 & S_ISSTATIC )
        inc i
        imul ebx,i,asm_tok
        add ebx,tokenarray
        .for ( : [ebx].token != T_FINAL && [ebx].token != T_COMMA : i++, ebx+=16 )
        .endf
    .endif

    mov fastcall_id,GetFastcallId( [esi].langtype )

    .if ( fastcall_id )

        fastcall_init()

        mov eax,fastcall_id
        dec eax
        imul ecx,eax,fastcall_conv
        mov porder,fastcall_tab[ecx].invokestart(
                   esi, numParam, i, tokenarray, &value )
    .endif

    mov edx,info
    assume edi:ptr dsym
    mov edi,[edx].proc_info.paralist
    mov parmpos,i

    .if ( !( [edx].proc_info.flags & PROC_HAS_VARARG ) )

        ;; check if there is a superfluous parameter in the INVOKE call
        .if ( PushInvokeParam( i, tokenarray, pproc, NULL, numParam, &r0flags ) != ERROR )
            .return( asmerr( 2136 ) )
        .endif
    .else

       .new k:int_t
        mov eax,Token_Count
        sub eax,i
        shr eax,1
        mov k,eax

        ;; for VARARG procs, just push the additional params with
        ;; the VARARG descriptor

        dec numParam
        mov size_vararg,0 ;; reset the VARARG parameter size count

        .while ( edi && !( [edi].sflags & S_ISVARARG ) )
            mov edi,[edi].nextparam
        .endw
        .for ( : k >= numParam: k-- )
            PushInvokeParam( i, tokenarray, pproc, edi, k, &r0flags )
        .endf

        ;; move to first non-vararg parameter, if any

        mov edx,info
        .for ( edi = [edx].proc_info.paralist : edi && [edi].sflags & S_ISVARARG : edi = [edi].nextparam )

        .endf
    .endif

    ;; the parameters are usually stored in "push" order.
    ;; This if() must match the one in proc.c, ParseParams().


    .if ( [esi].langtype == LANG_STDCALL || [esi].langtype == LANG_C || \
          [esi].langtype == LANG_SYSCALL || [esi].langtype == LANG_VECTORCALL || \
          ( ( [esi].langtype == LANG_WATCALL || [esi].langtype == LANG_FASTCALL ) && porder ) || \
          ( fastcall_id == FCT_WIN64 + 1 ) )

        ;; v2.23 if stack base is ESP

        .new total:int_t = 0

        .for ( : edi && numParam : edi = [edi].nextparam )
            dec numParam
            .if ( PushInvokeParam( i, tokenarray, pproc, edi, numParam, &r0flags ) == ERROR )
                .if ( !pmacro )
                    asmerr(2033, numParam)
                .endif
            .endif

            movzx eax,ModuleInfo.Ofssize
            mov eax,ModuleInfo.basereg[eax*4]
            .if ( CurrProc && eax == T_ESP )

                ;; The symbol offset is reset after the loop.
                ;; To have any effect the push-lines needs to
                ;; be processed here for each argument.

                RunLineQueue()

                ;; set push size to DWORD/QWORD

                mov eax,[edi].total_size
                .if (eax < 4)
                    mov eax,4
                .endif
                .if (eax > 4)
                    mov eax,8
                .endif
                add total,eax

                ;; Update arguments in the current proc if any
                mov ecx,CurrProc
                mov edx,[ecx].dsym.procinfo
                mov edx,[edx].proc_info.paralist
                .for ( : edx : edx = [edx].dsym.nextparam )
                    .if ( [edx].asym.state != SYM_TMACRO )
                        add [edx].asym.offs,eax
                    .endif
                .endf
            .endif
        .endf

        .if ( total )

            mov ecx,CurrProc
            mov eax,[ecx].dsym.procinfo
            mov edx,[eax].proc_info.paralist

            .for ( : edx : edx = [edx].dsym.nextparam )
                .if ( [edx].asym.state != SYM_TMACRO )
                    sub [edx].asym.offs,total
                .endif
            .endf
        .endif

    .else
        .for ( numParam = 0 : edi && !( [edi].sflags & S_ISVARARG ) : edi = [edi].nextparam, numParam++ )
            .if ( PushInvokeParam( i, tokenarray, pproc, edi, numParam, &r0flags ) == ERROR )
                .if ( !pmacro )
                    asmerr( 2033, numParam)
                .endif
            .endif
        .endf
    .endif

    mov i,j
    mov edx,info
    mov ecx,pproc
    .if ( !pmacro && \
          [ecx].asym.langtype == LANG_SYSCALL && \
          [edx].proc_info.flags & PROC_HAS_VARARG && \
          ModuleInfo.Ofssize == USE64 )
         .if ( porder )
            AddLineQueueX( " mov eax, %d", porder )
         .else
            AddLineQueue ( " xor eax, eax" )
         .endif
    .endif

    ;; v2.05 added. A warning only, because Masm accepts this.
    mov ecx,pproc
    mov edx,opnd.base_reg
    .if ( opnd.base_reg != NULL && Parse_Pass == PASS_1 && \
        (r0flags & R0_USED ) && [edx].asm_tok.bytval == 0 && !( [ecx].asym.flag1 & S_METHOD ) )
        asmerr( 7002 )
    .endif

    mov p,StringBufferEnd
    strcpy( p, " call " )
    add p,6

    .if ( !pmacro && [esi].state == SYM_EXTERNAL && [esi].dll )

        .new iatname:ptr = p
        strcpy( p, ModuleInfo.imp_prefix )
        add p,strlen( p )
        add p,Mangle( esi, p )
        inc namepos
        .if ( !( [esi].flags & S_IAT_USED ) )
            or [esi].flags,S_IAT_USED
            mov ecx,[esi].dll
            inc [ecx].dll_desc.cnt
            .if ( [esi].langtype != LANG_NONE && [esi].langtype != ModuleInfo.langtype )
                movzx eax,[esi].langtype
                add eax,T_CCALL - 1
                AddLineQueueX( " externdef %r %s: ptr proc", eax, iatname )
            .else
                AddLineQueueX( " externdef %s: ptr proc", iatname )
            .endif
        .endif
    .endif

    imul ebx,namepos,16
    add ebx,tokenarray
    mov ecx,opnd.mbr
    .if ( pmacro || ( [ebx].token == T_OP_SQ_BRACKET && \
        [ebx+3*16].token == T_DOT && ecx && [ecx].asym.flag1 & S_METHOD ) )

        .if ( pmacro )

            .new cnt:int_t = 0
            .new stk:int_t = 0
            .new args[128]:string_t

            mov ecx,StringBufferEnd
            inc ecx
            mov p,ecx
            strcpy( p, &buffer )
            strcat( p, "( " )
            add p,strlen(p)

            .if ( fastcall_id )

                mov edx,info
                .for ( edi = [edx].proc_info.paralist: edi: edi = [edi].nextparam, cnt++ )
                    mov eax,cnt
                    mov args[eax*4],NULL
                .endf

                .if ( [esi].langtype == LANG_WATCALL )
                    mov stk,4
                .elseif ( [esi].langtype == LANG_FASTCALL && ModuleInfo.Ofssize == USE32 )
                    mov stk,2
                .endif
                assume ebx:nothing
                .for ( ebx = 0: ebx < cnt: ebx++ )

                    .new reg:int_t = 0
                    mov eax,cnt
                    sub eax,ebx
                    dec eax
                    .new ind:int_t = eax

                    mov edx,info
                    .for ( edi = [edx].proc_info.paralist: ind: edi = [edi].nextparam, ind-- )
                    .endf

                    mov args[ebx*4],[edi].string_ptr
                    mov size,SizeFromMemtype( [edi].mem_type, [edi].Ofssize, [edi].type )

                    xor eax,eax
                    mov cl,[edi].mem_type
                    .if ( cl == MT_TYPE )
                        mov ecx,[edi].type
                        mov cl,[ecx].asym.mem_type
                    .endif

                    .if ( [esi].langtype == LANG_SYSCALL )
                        movzx eax,[edi].regist[0]
                    .elseif ( ebx < 4 )
                        .if ( cl & MT_FLOAT && size <= 16 )
                            lea eax,[ebx + T_XMM0]
                        .elseif ( cl == MT_YWORD )
                            lea eax,[ebx + T_YMM0]
                        .elseif ( cl == MT_ZWORD )
                            lea eax,[ebx + T_ZMM0]
                        .elseif ( ModuleInfo.Ofssize == USE64 || ebx < stk )
                            movzx eax,win64regs[ebx]
                        .endif
                    .elseif ( ebx < 6 && [esi].langtype == LANG_VECTORCALL )
                        .if ( cl & MT_FLOAT && size <= 16 )
                            lea eax,[ebx + T_XMM0]
                        .elseif ( cl == MT_YWORD )
                            lea eax,[ebx + T_YMM0]
                        .elseif ( cl == MT_ZWORD )
                            lea eax,[ebx + T_ZMM0]
                        .endif
                    .endif
                    mov reg,eax

                    .if ( [esi].langtype == LANG_WATCALL && ebx < 4 )
                        .if ( [edi].mem_type == MT_ABS )
                            mov args[ebx*4],[edi].name
                            mov [edi].name,&@CStr("")
                        .endif
                    .elseif ( [edi].mem_type == MT_ABS )
                        mov args[ebx*4],[edi].name
                        mov [edi].name,&@CStr("")
                    .elseif ( reg )
                        mov args[ebx*4],get_regname(reg, size)
                    .else
                        mov args[ebx*4],LclAlloc(16)
                        movzx eax,ModuleInfo.Ofssize
                        shl eax,2
                        .if ( ModuleInfo.Ofssize == USE64 )
                            tsprintf( args[ebx*4], "[rsp+%d*%d]", ebx, eax )
                        .else
                            mov ecx,ebx
                            sub ecx,stk
                            tsprintf( args[ebx*4], "[esp+%d*%d]", ecx, eax )
                        .endif
                    .endif
                .endf
            .endif

            assume ebx:ptr asm_tok

            imul ebx,i,16
            add ebx,tokenarray
            mov edx,info
            mov edi,pproc

            .if ( !cnt )

                .if ( [ebx].token != T_FINAL )

                    .if ( [edi].flag2 & S_ISSTATIC )
                        strcat( p, [ebx+32].tokpos )
                    .else
                        strcat( p, [ebx+16].tokpos )
                    .endif
                .endif

            .elseif ( [edx].proc_info.flags & PROC_HAS_VARARG )

                .if ( [ebx+16].tokval == T_ADDR && [edi].flag1 & S_METHOD )
                    strcat( p, [ebx+32].tokpos )
                .else
                    strcat( p, [ebx+16].tokpos )
                .endif
           .else
                push esi
                mov esi,1
                .if ( [edi].flag2 & S_ISSTATIC )
                    strcat( p, [ebx+32].string_ptr )
                    mov esi,0
                .else
                    strcat( p, args[0] )
                .endif
                .for ( : esi < cnt: esi++ )
                    strcat( p, ", " )
                    .if ( args[esi*4] )
                        strcat( p, args[esi*4] )
                    .endif
                .endf
                pop esi
            .endif
            strcat( p, ")" )

        .endif

        .if struct_ptr

            mov edi,T_EAX
            .if ( ModuleInfo.Ofssize == USE64 )
                .if ( [esi].langtype == LANG_SYSCALL )
                    mov edi,T_R10
                .else
                    mov edi,T_RAX
                .endif
            .endif
            mov ebx,struct_ptr
            mov ecx,SymSearch( [ebx].string_ptr )
            AssignPointer( ecx, edi, struct_ptr, pclass, [esi].langtype, pmacro)

        .elseif ( !pmacro )

            imul ebx,parmpos,16
            add ebx,tokenarray

            .if ( ModuleInfo.Ofssize == USE64 )

                .if ( [esi].langtype == LANG_SYSCALL )
                    AddLineQueue( " mov r10, [rdi]" )
                .else
                    AddLineQueue( " mov rax, [rcx]" )
                .endif
ifndef __ASMC64__
            .elseif ( ModuleInfo.Ofssize == USE32 )

                .new reg:int_t = T_EAX ;; v2.31 - skip mov eax,reg

                .if ( [esi].langtype == LANG_WATCALL )
                    ; do nothing: class in eax
                .elseif ( [esi].langtype == LANG_FASTCALL )
                    ; class in ecx
                    mov reg,T_ECX
                .elseif ( [ebx+16].tokval != T_EAX )

                    .if ( [ebx+16].token == T_REG && \
                          [ebx+16].tokval > T_EAX && \
                          [ebx+16].tokval <= T_EDI )
                        mov reg,[ebx+16].tokval
                    .elseif ( [ebx+16].token == T_RES_ID && \
                              [ebx+16].tokval == T_ADDR )
                        AddLineQueueX( " lea eax, %s", [ebx+32].string_ptr )
                    .else
                        AddLineQueueX( " mov eax, %s", [ebx+16].string_ptr )
                    .endif
                .endif
                AddLineQueueX( " mov eax, [%r]", reg )
endif
            .endif
        .endif
    .endif

    mov ebx,tokenarray
    imul edx,parmpos,16
    imul ecx,namepos,16

    .if ( pmacro == NULL )
        mov eax,[ebx+edx].tokpos
        sub eax,[ebx+ecx].tokpos
        mov size,eax
        memcpy( p, [ebx+ecx].tokpos, size )
        add eax,size
        mov byte ptr [eax],0
    .endif

    AddLineQueue( StringBufferEnd )

    mov edi,info
    mov esi,sym
    assume edi:ptr proc_info
    .if ( ( [esi].langtype == LANG_C || ( [esi].langtype == LANG_SYSCALL && !fastcall_id ) ) && \
        ( [edi].parasize || ( [edi].flags & PROC_HAS_VARARG && size_vararg ) ))

        movzx eax,ModuleInfo.Ofssize
        mov eax,stackreg[eax*4]

        .if ( [edi].flags & PROC_HAS_VARARG )
            mov ecx,[edi].parasize
            add ecx,size_vararg
            .if ( ModuleInfo.epilogueflags )
                AddLineQueueX( " lea %r, [%r+%u]", eax, eax, ecx )
            .else
                AddLineQueueX( " add %r, %u", eax, ecx )
            .endif
        .else
            .if ( ModuleInfo.epilogueflags )
                AddLineQueueX( " lea %r, [%r+%u]", eax, eax, [edi].parasize )
            .else
                AddLineQueueX( " add %r, %u", eax, [edi].parasize )
            .endif
        .endif
    .elseif ( fastcall_id )
        mov eax,fastcall_id
        dec eax
        imul ecx,eax,fastcall_conv
        fastcall_tab[ecx].invokeend( pproc, numParam, value )
    .endif
    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL )
    RunLineQueue()
    mov ecx,pmacro
    .if ( ecx && [ecx].asym.altname )
        mov edx,[ecx].asym.altname
        mov [edx],esi
    .endif
    .return( NOT_ERROR )

InvokeDirective endp

    end
