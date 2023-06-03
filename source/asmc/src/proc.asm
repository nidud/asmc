; PROC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  Processing of PROC/ENDP/LOCAL directives.
;

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include extern.inc
include equate.inc
include fixup.inc
include label.inc
include input.inc
include lqueue.inc
include tokenize.inc
include expreval.inc
include types.inc
include condasm.inc
include macro.inc
include proc.inc
include fastpass.inc
include listing.inc
include posndir.inc
include reswords.inc
include win64seh.inc
include hllext.inc
include qfloat.inc

define NUMQUAL

;
; STACKPROBE: emit a conditional "call __chkstk" inside the prologue
; if stack space that is to be allocated exceeds 1000h bytes.
; this is currently implemented for 64-bit only,
; if OPTION FRAME:AUTO is set and the procedure has the FRAME attribute.
; it's not active by default because, in a few cases, the listing might get messed.
;
define STACKPROBE 1

externdef szDgroup:char_t
externdef list_pos:uint_t ;; current LST file position
externdef strFUNC:sbyte

public  ProcStatus
public  procidx
public  StackAdj

define  T <@CStr>

.data

;
; Masm allows nested procedures
; but they must NOT have params or locals
;
; calling convention FASTCALL supports:
; - Watcom C: registers e/ax,e/dx,e/bx,e/cx
; - MS fastcall 16-bit: registers ax,dx,bx (default for 16bit)
; - MS fastcall 32-bit: registers ecx,edx (default for 32bit)
; - Win64: registers rcx, rdx, r8, r9 (default for 64bit)
;

CurrProc            ptr dsym 0  ;; current procedure
procidx             int_t 0     ;; procedure index

ProcStack           ptr proc_info 0

;
; v2.11: ProcStatus replaced DefineProc
;
ProcStatus          proc_status 0

endprolog_found     int_t 0
unw_segs_defined    db ?
align 8
unw_info            UNWIND_INFO <>
;
; v2.11: changed 128 -> 258; actually, 255 is the max # of unwind codes
;
unw_code            UNWIND_CODE 258 dup(<>)

align 8
;
; @ReservedStack symbol; used when option W64F_AUTOSTACKSP has been set
;
sym_ReservedStack   ptr asym 0 ;; max stack space required by INVOKE

;
; tables for FASTCALL support
;
; v2.07: 16-bit MS FASTCALL registers are AX, DX, BX.
; And params on stack are in PASCAL order.
;

ms64_regs           special_token T_RCX, T_RDX, T_R8, T_R9
;
; win64 non-volatile GPRs:
; T_RBX, T_RBP, T_RSI, T_RDI, T_R12, T_R13, T_R14, T_R15
;
win64_nvgpr         dw 0xF0E8
;
; win64 non-volatile XMM regs: XMM6-XMM15
;
win64_nvxmm         dw 0xFFC0

stackreg            uint_t T_SP, T_ESP, T_RSP
StackAdj            uint_t 0    ;; value of @StackBase variable
StackAdjHigh        int_t 0

    .code

    assume rbx:ptr asm_tok

ifdef FCT_ELF64
externdef elf64_regs:byte
endif

pushitem proc __ccall private stk:ptr, elmt:ptr

    LclAlloc( sizeof( qnode ) )
    mov rdx,stk
    mov rcx,[rdx]
    mov [rax].qnode.next,rcx
    mov rcx,elmt
    mov [rax].qnode.elmt,rcx
    mov [rdx],rax
    ret

pushitem endp


popitem proc __ccall private stk:ptr

    ldr rdx,stk
    mov rcx,[rdx]
    mov [rdx],[rcx].qnode.next
    mov rax,[rcx].qnode.elmt
    ret

popitem endp


push_proc proc __ccall private p:ptr dsym

    .if ( Parse_Pass == PASS_1 ) ;; get the locals stored so far
        SymGetLocal( p )
    .endif
    pushitem( &ProcStack, p )
    ret

push_proc endp


pop_proc proc __ccall private

    .if ( ProcStack == NULL )
        .return( NULL )
    .endif
    .return( popitem( &ProcStack ) )

pop_proc endp

;
; LOCAL directive. Syntax:
; LOCAL symbol[,symbol]...
; symbol:name [[count]] [:[type]]
; count: number of array elements, default is 1
; type:  qualified type [simple type, structured type, ptr to simple/structured type]
;

LocalDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local name  : string_t
  local loc   : ptr dsym
  local ti    : qualified_type

    .if ( Parse_Pass != PASS_1 ) ;; everything is done in pass 1
        .return( NOT_ERROR )
    .endif

    .if ( !( ProcStatus & PRST_PROLOGUE_NOT_DONE ) || CurrProc == NULL )
        .return( asmerr( 2012 ) )
    .endif

    mov rsi,CurrProc
    mov rsi,[rsi].dsym.procinfo
    assume rsi:ptr proc_info

    ; ensure the fpo bit is set - it's too late to set it in write_prologue().
    ; Note that the fpo bit is set only IF there are locals or arguments.
    ; fixme: what if pass > 1?

    movzx eax,[rsi].basereg
    .if ( GetRegNo( eax ) == 4 )
        or [rsi].flags,PROC_FPO
        or ProcStatus,PRST_FPO
    .endif

    inc i ; go past LOCAL
    mov rbx,tokenarray.tokptr(i)

    .repeat

        .if ( [rbx].token != T_ID )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif
        mov name,[rbx].string_ptr

        mov ti.symtype,NULL
        mov ti.is_ptr,0
        mov ti.ptr_memtype,MT_EMPTY
        mov eax,1
        mov cl,ModuleInfo._model
        shl eax,cl
        mov ti.is_far,FALSE
        .if ( eax & SIZE_DATAPTR )
            mov ti.is_far,TRUE
        .endif
        mov ti.Ofssize,ModuleInfo.Ofssize

        mov loc,SymLCreate( name )
        .if ( !eax )  ;; if it failed, an error msg has been written already
            .return( ERROR )
        .endif

        mov [rax].asym.state,SYM_STACK
        or  [rax].asym.flags,S_ISDEFINED
        mov [rax].asym.total_length,1 ;; v2.04: added
        .switch ( ti.Ofssize )
        .case USE16
            mov [rax].asym.mem_type,MT_WORD
            mov ti.size,sizeof( uint_16 )
            .endc
        .default
            mov [rax].asym.mem_type,MT_DWORD
            mov ti.size,sizeof( uint_32 )
            .endc
        .endsw

        inc i ; go past name
        add rbx,asm_tok

        ; get the optional index factor: local name[xx]:...

        .if ( [rbx].token == T_OP_SQ_BRACKET )

           .new opndx:expr

            inc i ; go past '['
            add rbx,asm_tok

            ; scan for comma or colon. this isn't really necessary,
            ; but will prevent the expression evaluator from emitting
            ; confusing error messages.

            .for ( ecx = i, rdx = rbx: ecx < Token_Count: ecx++, rdx += asm_tok )
                .break .if ( [rdx].asm_tok.token == T_COMMA || [rdx].asm_tok.token == T_COLON )
            .endf
            .return .ifd ( EvalOperand( &i, tokenarray, ecx, &opndx, 0 ) == ERROR )

            .if ( opndx.kind != EXPR_CONST )
                asmerr( 2026 )
                mov opndx.value,1
            .endif

            ; zero is allowed as value!

            mov rbx,tokenarray.tokptr(i)
            mov rcx,loc
            mov [rcx].asym.total_length,opndx.value
            or  [rcx].asym.flags,S_ISARRAY
            .if ( [rbx].token == T_CL_SQ_BRACKET )
                inc i ; go past ']'
                add rbx,asm_tok
            .else
                asmerr( 2045 )
            .endif
        .endif


        ; get the optional type: local name[xx]:type

        .if ( [rbx].token == T_COLON )

            inc i
            .return .ifd ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )

            mov rbx,tokenarray.tokptr(i)
            mov rcx,loc
            mov [rcx].asym.mem_type,ti.mem_type
            .if ( ti.mem_type == MT_TYPE )
                mov [rcx].asym.type,ti.symtype
            .else
                mov [rcx].asym.target_type,ti.symtype
            .endif
        .endif
        mov rcx,loc
        mov [rcx].asym.is_ptr,ti.is_ptr
        mov [rcx].asym.is_far,ti.is_far
        mov [rcx].asym.Ofssize,ti.Ofssize
        mov [rcx].asym.ptr_memtype,ti.ptr_memtype
        mov eax,ti.size
        mul [rcx].asym.total_length
        mov [rcx].asym.total_size,eax

        ; v2.12: address calculation is now done in SetLocalOffsets()

        .if ( [rsi].locallist == NULL )
            mov [rsi].locallist,rcx
        .else
            .for( rdx = [rsi].locallist: [rdx].dsym.nextlocal : rdx = [rdx].dsym.nextlocal )
            .endf
            mov [rdx].dsym.nextlocal,rcx
        .endif

        .if ( [rbx].token != T_FINAL )
            .if ( [rbx].token == T_COMMA )
                mov eax,i
                inc eax
                .if ( eax < Token_Count )
                    inc i
                    add rbx,asm_tok
                .endif
            .else
                .return( asmerr( 2065, "," ) )
            .endif
        .endif
    .until ( i >= Token_Count )
    .return( NOT_ERROR )

LocalDir endp

;
; read/write value of @StackBase variable
;

UpdateStackBase proc fastcall sym:ptr asym, opnd:ptr expr

    .if ( rdx )
        mov StackAdj,[rdx].expr.uvalue
        mov StackAdjHigh,[rdx].expr.hvalue
    .endif
    mov [rcx].asym.value,StackAdj
    mov [rcx].asym.value3264,StackAdjHigh
    ret

UpdateStackBase endp

;
; read value of @ProcStatus variable
;

UpdateProcStatus proc fastcall sym:ptr asym, opnd:ptr expr

    xor eax,eax
    .if ( CurrProc )
        mov eax,ProcStatus
    .endif
    mov [rcx].asym.value,eax
    ret

UpdateProcStatus endp

;
; Added v2.27
;

GetFastcallId proc fastcall langtype:int_t

    movzx edx,ModuleInfo.Ofssize
    .if ( ecx == LANG_FASTCALL )
        .if ( edx == USE64 )
            .return FCT_WIN64 + 1
        .elseif ( Options.fctype == FCT_WATCOMC )
            .return FCT_WATCOMC + 1
        .endif
        .return FCT_MSC + 1
    .elseif ( ecx == LANG_SYSCALL )
        .if ( edx == USE64 )
            .return FCT_ELF64 + 1
        .endif
    .elseif ( ecx == LANG_VECTORCALL )
        .if ( edx == USE64 )
            .return FCT_VEC64 + 1
        .endif
        .return FCT_VEC32 + 1
    .elseif ( ecx == LANG_WATCALL )
        .return FCT_WATCOMC + 1
    .endif
    .return 0

GetFastcallId endp

;
; parse parameters of a PROC/PROTO.
; Called in pass one only.
; i=start parameters
;

MacroInline proto __ccall :string_t, :int_t, :string_t, :string_t, :int_t

ParseInline proc __ccall private uses rsi rbx sym:ptr asym, curr:ptr asm_tok, tokenarray:ptr asm_tok

    .if ( Parse_Pass == PASS_1 )

        ldr rcx,sym
        or [rcx].asym.flags,S_ISINLINE

        xor esi,esi
        xor eax,eax
        mov rbx,curr
        mov rcx,tokenarray
        add rcx,2*asm_tok

        .if ( [rcx].asm_tok.token == T_RES_ID &&
              [rcx].asm_tok.tokval >= T_CCALL &&
              [rcx].asm_tok.tokval <= T_WATCALL )
            add rcx,asm_tok
        .endif

        .for ( rdx = rcx: rdx < rbx: rdx += asm_tok )
            .if ( [rdx].asm_tok.token == T_COLON )
                inc esi
            .elseif ( rdx > rcx && [rdx].asm_tok.token == T_COMMA )
                inc eax
            .endif
        .endf

        .if ( eax > esi )
            inc eax
            mov esi,eax
        .endif

        mov [rbx].token,T_FINAL
        mov rax,[rbx].tokpos
        mov byte ptr [rax],0

        .if ( [rdx-asm_tok].asm_tok.token == T_RES_ID && [rdx-asm_tok].asm_tok.tokval == T_VARARG )
            mov edx,1
        .else
            xor edx,edx
        .endif

        mov rax,tokenarray
        MacroInline([rax].asm_tok.string_ptr, esi, [rcx].asm_tok.tokpos, [rbx].string_ptr, edx )
    .endif
    ret

ParseInline endp


ParseParams proc __ccall private uses rsi rdi rbx p:ptr dsym, i:int_t, tokenarray:ptr asm_tok, IsPROC:int_t

   .new name:string_t
   .new sym:ptr dsym
   .new cntParam:int_t
   .new offs:int_t
   .new fcint:int_t = 0
   .new ti:qualified_type
   .new is_vararg:int_t
   .new init_done:int_t
   .new paranode:ptr dsym
   .new paracurr:ptr dsym
   .new curr:int_t
   .new ParamReverse:int_t = 0 ; Reverse direction

    ldr rcx,p
    mov rsi,[rcx].dsym.procinfo
    movzx edi,[rcx].asym.langtype
   .new fastcall_id:int_t = GetFastcallId( edi )

    ; find "first" parameter ( that is, the first to be pushed in INVOKE )

    .if ( edi == LANG_STDCALL || edi == LANG_C || edi == LANG_SYSCALL || edi == LANG_VECTORCALL ||
          ( edi == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) || edi == LANG_WATCALL )
        mov ParamReverse,1
    .endif

    mov rdi,[rsi].paralist
    .if ( ParamReverse )
        .for ( : rdi && [rdi].dsym.nextparam : rdi = [rdi].dsym.nextparam )
        .endf
    .endif
    mov paracurr,rdi


    ; v2.11: proc_info.init_done has been removed, sym.isproc flag is used instead

    mov rcx,p
    mov eax,[rcx].asym.flags
    and eax,S_ISPROC
    mov init_done,eax

    mov rbx,tokenarray.tokptr(i)
    .for ( cntParam = 0 : [rbx].token != T_FINAL : cntParam++ )

        .if ( [rbx].token == T_ID )
            mov name,[rbx].string_ptr
            inc i
            add rbx,asm_tok
        .elseif ( IsPROC == FALSE && [rbx].token == T_COLON )
            .if ( rdi )
                mov name,[rdi].asym.name
            .else
                mov name,&@CStr("")
            .endif
        .else

            ; PROC needs a parameter name, PROTO accepts <void> also

            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif

        mov ti.symtype,NULL
        mov ti.is_ptr,0
        mov ti.ptr_memtype,MT_EMPTY
        mov eax,1
        mov cl,ModuleInfo._model
        shl eax,cl
        .if ( eax & SIZE_DATAPTR )
            mov ti.is_far,TRUE
        .else
            mov ti.is_far,FALSE
        .endif
        mov ti.Ofssize,ModuleInfo.Ofssize
        mov ti.size,CurrWordSize
        mov is_vararg,FALSE


        ; read colon. It's optional for PROC.
        ; Masm also allows a missing colon for PROTO - if there's
        ; just one parameter. Probably a Masm bug.
        ; JWasm always require a colon for PROTO.


        .if ( [rbx].token != T_COLON )

            .if ( IsPROC == FALSE )
                .return( asmerr( 2065, ":" ) )
            .endif
            mov ti.mem_type,MT_WORD
            .if ( ti.Ofssize != USE16 )
                mov ti.mem_type,MT_DWORD
            .endif

        .else

            inc i
            add rbx,asm_tok

            .if ( ( [rbx].token == T_RES_ID ) && ( [rbx].tokval == T_VARARG ) )

                mov rcx,p
                movzx eax,[rcx].asym.langtype

                .switch( eax )
                .case LANG_NONE
                .case LANG_BASIC
                .case LANG_FORTRAN
                .case LANG_PASCAL
                .case LANG_STDCALL
                    .return( asmerr( 2131 ) )
                .endsw

                ; v2.05: added check

                .if ( ( [rbx+asm_tok].token == T_FINAL ) ||
                     ( [rbx+asm_tok].token == T_STRING && [rbx+asm_tok].string_delim == '{' ) )
                    mov is_vararg,TRUE
                .else
                    asmerr( 2129 )
                .endif

                mov ti.mem_type,MT_EMPTY
                mov ti.size,0
                inc i

            .else

                xor eax,eax
                .if ( [rbx].token == T_ID )
                    mov rcx,[rbx].string_ptr
                    mov eax,[rcx]
                    or  eax,0x202020
                .endif
                .if ( eax == 'sba' )
                    mov ti.mem_type,MT_ABS
                    inc i
                .elseifd ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                    .return
                .endif
            .endif
        .endif


        ; check if parameter name is defined already

        .if ( IsPROC )
            .if SymSearch( name )
                .if ( [rax].asym.state != SYM_UNDEFINED )
                    .return( asmerr( 2005, name ) )
                .endif
            .endif
        .endif


        ; redefinition?

        .if ( paracurr )

            .new to:ptr asym
            .new tn:ptr asym
            .new oo:char_t
            .new on:char_t
            .new fast_type:char_t = 0

            .for ( rcx = ti.symtype : rcx && [rcx].asym.type : rcx = [rcx].asym.type )
            .endf
            mov tn,rcx

            ; v2.12: don't assume pointer type if mem_type is != MT_TYPE!
            ; regression test proc9.asm.
            ; v2.23: proto fastcall :type - fast32.asm

            mov rdi,paracurr

            .if ( fastcall_id == FCT_VEC32 + 1 || fastcall_id == FCT_MSC + 1 ||
                 ( !( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) && fastcall_id == FCT_ELF64 + 1 ) )

                mov [rdi].asym.target_type,NULL
                .if ( !ModuleInfo.strict_masm_compat )
                    mov fast_type,1 ; v2.27 added
                .endif
            .endif
            .if ( [rdi].asym.mem_type == MT_TYPE )
                mov rdx,[rdi].asym.type
            .else
                xor edx,edx
                .if ( [rdi].asym.mem_type == MT_PTR )
                    mov rdx,[rdi].asym.target_type
                .endif
            .endif
            .for( : rdx && [rdx].asym.type : rdx = [rdx].asym.type )
            .endf
            mov to,rdx
            mov al,ModuleInfo.Ofssize
            mov ah,al
            .if ( [rdi].asym.Ofssize != USE_EMPTY )
                mov al,[rdi].asym.Ofssize
            .endif
            mov oo,al
            .if ( ti.Ofssize != USE_EMPTY )
                mov ah,ti.Ofssize
            .endif
            mov on,ah

            .if ( ti.mem_type != [rdi].asym.mem_type || ( ti.mem_type == MT_TYPE && tn != to ) ||
                  ( ti.mem_type == MT_PTR && ( ti.is_far != [rdi].asym.is_far || on != oo ||
                  ( !fast_type && ( ti.ptr_memtype != [rdi].asym.ptr_memtype || tn != to ) ) ) ) )
                asmerr( 2111, name )
            .endif
            .if ( IsPROC )

                ; it has been checked already that the name isn't found
                ; - SymAddLocal() shouldn't fail

                SymAddLocal( rdi, name )
            .endif

            ; set paracurr to next parameter

            .if ( ParamReverse )
                .for ( rcx = [rsi].paralist: rcx && [rcx].dsym.nextparam != rdi : rcx = [rcx].dsym.nextparam )
                .endf
            .else
                mov rcx,[rdi].dsym.nextparam
            .endif
            mov paracurr,rcx

        .elseif ( init_done )

            ; second definition has more parameters than first

            .return( asmerr( 2111, "" ) )
        .else
            .if ( IsPROC )
                mov rdi,SymLCreate( name )
            .else
                mov rdi,SymAlloc( "" )  ; for PROTO, no param name needed
            .endif
            .if ( rdi == NULL )         ; error msg has been displayed already
                .return( ERROR )
            .endif
            mov paranode,rdi
            or  [rdi].asym.flags,S_ISDEFINED
            mov [rdi].asym.mem_type,ti.mem_type
            .if ( ti.mem_type == MT_TYPE )
                mov [rdi].asym.type,ti.symtype
            .else
                mov [rdi].asym.target_type,ti.symtype
            .endif

            ; v2.05: moved BEFORE fastcall_tab()

            mov [rdi].asym.is_far,ti.is_far
            mov [rdi].asym.Ofssize,ti.Ofssize
            mov [rdi].asym.is_ptr,ti.is_ptr
            mov [rdi].asym.ptr_memtype,ti.ptr_memtype
            .if ( is_vararg )
                or [rdi].asym.sflags,S_ISVARARG
            .endif

            mov eax,fastcall_id
            .if eax
                dec eax
                imul ecx,eax,fastcall_conv
ifdef _WIN64
                lea rax,fastcall_tab
                add rax,rcx
                [rax].fastcall_conv.paramcheck( p, rdi, &fcint )
else
                fastcall_tab[ecx].paramcheck( p, edi, &fcint )
endif
            .endif
            .if ( eax == 0 )
                mov [rdi].asym.state,SYM_STACK
            .endif

            mov [rdi].asym.total_length,1 ; v2.04: added
            mov [rdi].asym.total_size,ti.size

            .if ( !( [rdi].asym.sflags & S_ISVARARG ) )

                ; v2.11: CurrWordSize does reflect the default parameter size only for PROCs.
                ;
                ; For PROTOs and TYPEs use member seg_ofssize.

                mov eax,2
                mov rcx,p
                mov cl,[rcx].asym.segoffsize
                shl eax,cl
                .if ( IsPROC )
                    movzx eax,CurrWordSize
                .endif
                mov ecx,ROUND_UP( ti.size, eax )
                add [rsi].parasize,ecx
            .endif


            ; Parameters usually are stored in "push" order.
            ; However, for Win64, it's better to store them
            ; the "natural" way from left to right, since the
            ; arguments aren't "pushed".

            mov rcx,p
            movzx eax,[rcx].asym.langtype
            .switch( eax )
            .case LANG_BASIC
            .case LANG_FORTRAN
            .case LANG_PASCAL
            left_to_right:
                mov [rdi].dsym.nextparam,NULL
                .if ( [rsi].paralist == NULL )
                    mov [rsi].paralist,rdi
                .else
                    .for ( rdx = [rsi].paralist: rdx: rdx = [rdx].dsym.nextparam )
                        .break .if ( [rdx].dsym.nextparam == NULL )
                    .endf
                    mov [rdx].dsym.nextparam,rdi
                    mov paracurr,NULL
                .endif
                .endc
            .case LANG_FASTCALL

                ; v2.07: MS fastcall 16-bit is PASCAL!

                .if ( ti.Ofssize == USE16 && ModuleInfo.fctype == FCT_MSC )
                    jmp left_to_right
                .endif
            .default
                mov [rdi].dsym.nextparam,[rsi].paralist
                mov [rsi].paralist,rdi
                .endc
            .endsw
        .endif

        mov rbx,tokenarray.tokptr(i)

        .if ( [rbx].token != T_FINAL )
            .if ( [rbx].token != T_COMMA )
                .if ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_EQU && \
                      [rbx+asm_tok].token == T_STRING && [rbx+asm_tok].bytval == '<' )

                    mov rcx,[rbx-asm_tok].string_ptr
                    mov eax,[rcx]
                    or  eax,0x202020
                    .if ( [rbx-asm_tok].token != T_ID || eax != 'sba' )
                        .return( asmerr( 2008, [rbx-asm_tok].tokpos ) )
                    .endif
                    add i,2 ; v2.32.16 - name:abs=<val>
                    add rbx,2*asm_tok
                .endif

                mov rcx,tokenarray
                .if ( [rbx].token == T_STRING &&
                      [rbx].string_delim == '{' &&
                      [rcx+asm_tok].asm_tok.tokval == T_PROTO )

                    ParseInline(p, rbx, tokenarray)

                .elseif ( [rbx].token != T_COMMA )

                    .return( asmerr( 2065, "," ) )
                .endif
            .endif
            inc i ; go past comma
            add rbx,asm_tok
        .endif
    .endf

    .if ( init_done )
        .if ( paracurr )

            ; first definition has more parameters than second

            .return( asmerr( 2111, "" ) )
        .endif
    .endif

    .if ( IsPROC )

        ; calc starting offset for parameters,
        ; offset from [E|R]BP : return addr + old [E|R]BP
        ; NEAR: 2 * wordsize, FAR: 3 * wordsize
        ;        NEAR  FAR
        ;-------------------------
        ; USE16   +4   +6
        ; USE32   +8   +12
        ; USE64   +16  +24
        ; without frame pointer:
        ; USE16   +2   +4
        ; USE32   +4   +8
        ; USE64   +8   +16

        mov eax,2
        mov rcx,p
        .if ( [rcx].asym.mem_type == MT_FAR )
            inc eax
        .endif
        movzx ecx,CurrWordSize
        mul ecx
        mov offs,eax

        ; now calculate the [E|R]BP offsets

        .for ( : cntParam : cntParam-- )
            .for ( ebx = 1, rdi = [rsi].paralist: ebx < cntParam : rdi = [rdi].dsym.nextparam, ebx++ )
            .endf
            .if ( [rdi].asym.state != SYM_TMACRO ) ; register param?

                mov   [rdi].asym.offs,offs
                or    [rsi].flags,PROC_STACKPARAM
                movzx ecx,CurrWordSize
                mov   ebx,ROUND_UP( [rdi].asym.total_size, ecx )
                movzx ecx,CurrWordSize

                .if ( ebx > ecx && [rdi].asym.mem_type == MT_TYPE )
                    mov ebx,ecx ; large types to pointer..
                .endif
                add offs,ebx
            .endif
        .endf
    .endif
    .return ( NOT_ERROR )

ParseParams endp

;
; parse a function prototype - called in pass 1 only.
; the syntax is used by:
; - PROC directive:     <name> PROC ...
; - PROTO directive:    <name> PROTO ...
; - EXTERN[DEF] directive: EXTERN[DEF] <name>: PROTO ...
; - TYPEDEF directive:          <name> TYPEDEF PROTO ...
;
; i = start index of attributes
; IsPROC: TRUE for PROCs, FALSE for everything else
;
; strategy to set default value for "offset size" (16/32):
; 1. if current model is FLAT, use 32, else
; 2. use the current segment's attribute
; 3. if no segment is set, use cpu setting
;

ParseProc proc __ccall uses rsi rdi rbx p:ptr dsym,
        i:int_t, tokenarray:ptr asm_tok, IsPROC:int_t, langtype:byte

  .new token:string_t
  .new regist:ptr word
  .new newmemtype:byte
  .new newofssize:byte
  .new oldofssize:byte
  .new oldpublic:int_t
  .new Ofssize:byte

    ldr rdi,p
    mov rsi,[rdi].dsym.procinfo
    mov eax,[rdi].asym.flags
    and eax,S_ISPUBLIC
    mov oldpublic,eax

    ; set some default values

    .if ( IsPROC )

        and [rsi].flags,not PROC_ISEXPORT
        .if ( ModuleInfo.procs_export )
            or [rsi].flags,PROC_ISEXPORT
        .endif

        ; don't overwrite a PUBLIC directive for this symbol!

        .if ( ModuleInfo.procs_private == FALSE )
            or [rdi].asym.flags,S_ISPUBLIC
        .endif

        ; set type of epilog code
        ; v2.11: if base register isn't [E|R]BP, don't use LEAVE!

        mov ebx,ModuleInfo.curr_cpu
        and ebx,P_CPU_MASK
        xor edi,edi
        movzx ecx,[rsi].basereg

        .if ( GetRegNo( ecx ) != 5 )

        .elseif ( Options.masm_compat_gencode )

            ; v2.07: Masm uses LEAVE if
            ; - current code is 32-bit/64-bit or
            ; - cpu is .286 or .586+

            .if ( ModuleInfo.Ofssize > USE16 || ebx == P_286 || ebx >= P_586 )
                inc edi
            .endif
        .else

            ; use LEAVE for 286, 386 (and x64)

            .if ( ebx == P_286 || ebx == P_64 || ebx == P_386 )
                inc edi
            .endif
        .endif
        .if ( edi )
            or [rsi].flags,PROC_PE_TYPE
        .endif
    .endif

    ; 1. attribute is <distance>

    mov rbx,tokenarray.tokptr(i)
    .if ( [rbx].token == T_STYPE &&
          [rbx].tokval >= T_NEAR && [rbx].tokval <= T_FAR32 )

        mov Ofssize,GetSflagsSp( [rbx].tokval )
        .if ( IsPROC )
            .if ( ( ModuleInfo.Ofssize >= USE32 && al == USE16 ) ||
                  ( ModuleInfo.Ofssize == USE16 && al == USE32 ) )
                asmerr( 2011 )
            .endif
        .endif

        mov newmemtype,GetMemtypeSp( [rbx].tokval )
        mov al,Ofssize
        .if ( al == USE_EMPTY )
            mov al,ModuleInfo.Ofssize
        .endif
        mov newofssize,al
        inc i

    .else

        mov eax,1
        mov cl,ModuleInfo._model
        shl eax,cl
        and eax,SIZE_CODEPTR
        .if eax
            mov eax,MT_FAR
        .else
            mov eax,MT_NEAR
        .endif
        mov newmemtype,al
        mov newofssize,ModuleInfo.Ofssize
    .endif

    ;
    ; v2.11: GetSymOfssize() cannot handle SYM_TYPE correctly
    ;
    mov rdi,p
    .if ( [rdi].asym.state == SYM_TYPE )
        mov oldofssize,[rdi].asym.segoffsize
    .else
        mov oldofssize,GetSymOfssize( rdi )
    .endif

    ; did the distance attribute change?

    .if ( [rdi].asym.mem_type != MT_EMPTY &&
          ( [rdi].asym.mem_type != newmemtype || oldofssize != newofssize ) )

        .if ( [rdi].asym.mem_type == MT_NEAR || [rdi].asym.mem_type == MT_FAR )
            asmerr( 2112 )
        .else
            .return( asmerr( 2005, [rdi].asym.name ) )
        .endif
    .else
        mov [rdi].asym.mem_type,newmemtype
        .if ( IsPROC == FALSE )
            mov [rdi].asym.segoffsize,newofssize
        .endif
    .endif

    ; 2. attribute is <langtype>
    ; v2.09: the default language value is now a function argument. This is because
    ; EXTERN[DEF] allows to set the language attribute by:
    ; EXTERN[DEF] <langtype> <name> PROTO ...
    ; ( see CreateProto() in extern.asm )

    GetLangType( &i, tokenarray, &langtype ) ; optionally overwrite the value

    ; has language changed?

    .if ( [rdi].asym.langtype != LANG_NONE && [rdi].asym.langtype != langtype )
        asmerr( 2112 )
    .else
        mov [rdi].asym.langtype,langtype
    .endif

    ; 3. attribute is <visibility>
    ; note that reserved word PUBLIC is a directive!
    ; PROTO does NOT accept PUBLIC! However,
    ; PROTO accepts PRIVATE and EXPORT, but these attributes are just ignored!

    mov rbx,tokenarray.tokptr(i)

    .if ( [rbx].token == T_ID || [rbx].token == T_DIRECTIVE )

        mov token,[rbx].string_ptr

        .ifd ( tstricmp( rax, "PRIVATE") == 0 )

            .if ( IsPROC )  ; v2.11: ignore PRIVATE for PROTO

                and [rdi].asym.flags,not S_ISPUBLIC

                ; error if there was a PUBLIC directive!

                or [rdi].asym.flags,S_SCOPED
                .if ( oldpublic )
                    SkipSavedState() ; do a full pass-2 scan
                .endif
                and [rsi].flags,not PROC_ISEXPORT
            .endif
            inc i

        .elseifd ( tstricmp( token, "PUBLIC" ) == 0 )

            .if ( IsPROC )
                or  [rdi].asym.flags,S_ISPUBLIC
                and [rsi].flags,not PROC_ISEXPORT
            .endif
            inc i

        .elseifd ( tstricmp(token, "EXPORT") == 0 )

            .if ( IsPROC )  ; v2.11: ignore EXPORT for PROTO

                or [rdi].asym.flags,S_ISPUBLIC
                or [rsi].flags,PROC_ISEXPORT

                ; v2.11: no export for 16-bit near

                .if ( ModuleInfo.Ofssize == USE16 && [rdi].asym.mem_type == MT_NEAR )
                    asmerr( 2145, [rdi].asym.name )
                .endif
            .endif
            inc i
        .endif
    .endif

    ; 4. attribute is <prologuearg>, for PROC only.
    ; it must be enclosed in <>

    .if ( IsPROC && [rbx].token == T_STRING && [rbx].string_delim == '<' )

        mov edi,Token_Count
        inc edi

        .new max:int_t

        .if ( ModuleInfo.prologuemode == PEM_NONE )

            ; no prologue at all

        .elseif ( ModuleInfo.prologuemode == PEM_MACRO )

            mov [rsi].prologuearg,LclDup( [rbx].string_ptr )

        .else

            ; check the argument. The default prologue
            ;
            ; understands FORCEFRAME and LOADDS only

            mov max,Tokenize( [rbx].string_ptr, edi, tokenarray, TOK_RESCAN )

            .for ( : edi < max: edi++ )

                mov rbx,tokenarray.tokptr(edi)

                .if ( [rbx].token == T_ID )

                    .ifd ( tstricmp( [rbx].string_ptr, "FORCEFRAME") == 0 )

                        or [rsi].flags,PROC_FORCEFRAME

                    .else

                        .if ( ModuleInfo.Ofssize != USE64 )

                            .ifd ( tstricmp( [rbx].string_ptr, "LOADDS") == 0 )

                                .if ( ModuleInfo._model == MODEL_FLAT )
                                    asmerr( 8014 )
                                .else
                                    or [rsi].flags,PROC_LOADDS
                                .endif
                            .else
                                .return( asmerr( 4005, [rbx].string_ptr ) )
                            .endif
                        .else
                            .return( asmerr( 4005, [rbx].string_ptr ) )
                        .endif
                    .endif
                    .if ( [rbx+asm_tok].token == T_COMMA && [rbx+2*asm_tok].token != T_FINAL)
                        inc edi
                    .endif
                .else
                    .return( asmerr( 2008, [rbx].string_ptr ) )
                .endif
            .endf
        .endif
        inc i
    .endif

    ; check for optional FRAME[:exc_proc]

    imul ebx,i,asm_tok
    add rbx,tokenarray
    mov rdi,p
    mov cl,[rdi].asym.langtype

    .if ( ModuleInfo.Ofssize == USE64 && IsPROC )

        mov [rsi].exc_handler,NULL
        .if ( [rbx].token == T_RES_ID && [rbx].tokval == T_FRAME )
            ;
            ; v2.05: don't accept FRAME for ELF
            ;
            .if ( Options.output_format == OFORMAT_ELF ||
                  Options.output_format == OFORMAT_OMF ||
                  ModuleInfo.sub_format == SFORMAT_MZ )

                .return( asmerr( 3006, GetResWName( T_FRAME, NULL ) ) )
            .endif

            inc i
            add rbx,asm_tok

            .if ( [rbx].token == T_COLON )

                inc i
                add rbx,asm_tok

                .if ( [rbx].token != T_ID )
                    .return( asmerr(2008, [rbx].string_ptr ) )
                .endif

                mov rdi,SymSearch( [rbx].string_ptr )

                .if ( rax == NULL )

                    mov rdi,SymCreate( [rbx].string_ptr )
                    mov [rax].asym.state,SYM_UNDEFINED
                    or  [rax].asym.flags,S_USED
                    sym_add_table( &SymTables[TAB_UNDEF*symbol_queue], rax ) ; add UNDEFINED

                .elseif ( [rax].asym.state != SYM_UNDEFINED &&
                       [rax].asym.state != SYM_INTERNAL && [rax].asym.state != SYM_EXTERNAL )

                    .return( asmerr( 2005, [rax].asym.name ) )
                .endif

                mov [rsi].exc_handler,rdi
                inc i
                add rbx,asm_tok
            .endif

            or [rsi].flags,PROC_ISFRAME
        .elseif ( ModuleInfo.frame_auto == 3 && ( cl == LANG_FASTCALL || cl == LANG_VECTORCALL ) )
            or [rsi].flags,PROC_ISFRAME
        .endif
    .endif

    ; check for USES

    .if ( [rbx].token == T_ID )

        mov rcx,[rbx].string_ptr
        mov eax,[rcx]
        or  eax,0x20202020

        .if ( eax == 'sesu' && byte ptr [rcx+4] == 0 )

            .new cnt:int_t
            .new j:int_t
            .new index:int_t
            .new sym:ptr asym

            .if ( !IsPROC ) ; not for PROTO!
                asmerr( 2008, [rbx].string_ptr )
            .endif
            inc i
            add rbx,asm_tok

            ; count register names which follow

            .for ( cnt = 0 : : cnt++, rbx += asm_tok )

                .if ( [rbx].token != T_REG )

                    ; the register may be a text macro here

                    .break .if ( [rbx].token != T_ID )
                    .break .if ( ( SymSearch( [rbx].string_ptr ) ) == NULL )

                    .break .if ( [rax].asym.state != SYM_TMACRO )
                    mov rdi,rax
                    mov ecx,FindResWord( [rdi].asym.string_ptr, [rdi].asym.name_size )
                    imul eax,ecx,special_item
                    lea rdx,SpecialTable
                    .break .if ( [rdx+rax].special_item.type != RWT_REG )

                    mov [rbx].token,T_REG
                    mov [rbx].tokval,ecx
                    mov [rbx].string_ptr,[rdi].asym.string_ptr
                .endif
            .endf
            mov rbx,tokenarray.tokptr(i)

            .if ( cnt == 0 )

                asmerr( 2008, [rbx-asm_tok].tokpos )

            .else

                mov ecx,cnt
                inc ecx
                imul ecx,ecx,sizeof( uint_16 )
                mov rdi,LclAlloc( ecx )
                mov [rsi].regslist,rdi
                mov eax,cnt
                stosw

                ; read in registers

                .for ( : [rbx].token == T_REG: i++, rbx += asm_tok )

                    .if ( SizeFromRegister( [rbx].tokval ) == 1 )
                        asmerr( 2032 )
                    .endif
                    mov eax,[rbx].tokval
                    stosw
                .endf
            .endif
        .endif
    .endif

    ; the parameters must follow

    .if ( [rbx].token == T_STYPE || [rbx].token == T_RES_ID || [rbx].token == T_DIRECTIVE )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif

    ; skip optional comma

    .if ( [rbx].token == T_COMMA )
        inc i
        add rbx,asm_tok
    .endif

    mov rdi,p
    .if ( i >= Token_Count || ( [rbx].token == T_STRING && [rbx].string_delim == '{' ) )

        ; procedure has no parameters at all

        .if ( [rsi].paralist != NULL )
            asmerr( 2111, "" )
        .endif
        .if ( [rbx].token == T_STRING && [rbx].string_delim == '{' )
            ParseInline(rdi, rbx, tokenarray)
        .endif

    .elseif ( [rdi].asym.langtype == LANG_NONE )
        asmerr( 2119 )
    .else

        ; v2.05: set PROC's vararg flag BEFORE params are scanned!

        mov ebx,Token_Count ; v2.31: proto :vararg {
        dec ebx
        mov rbx,tokenarray.tokptr(ebx)

        .if ( [rbx].token == T_STRING && [rbx].string_delim == '{' )
            sub rbx,asm_tok
        .endif
        .if ( [rbx].token == T_RES_ID && [rbx].tokval == T_VARARG )
            or [rsi].flags,PROC_HAS_VARARG
        .endif
        .ifd ( ParseParams( rdi, i, tokenarray, IsPROC ) == ERROR )

            ; do proceed if the parameter scan returns an error
        .endif
    .endif

    ; v2.11: isdefined and isproc now set here

    or [rdi].asym.flags,S_ISDEFINED
    or [rdi].asym.flags,S_ISPROC
   .return( NOT_ERROR )

ParseProc endp


; create a proc ( internal[=PROC] or external[=PROTO] ) item.
; sym is either NULL, or has type SYM_UNDEFINED or SYM_EXTERNAL.
; called by:
; - ProcDir ( state == SYM_INTERNAL )
; - CreateLabel ( state == SYM_INTERNAL )
; - AddLinnumDataRef ( state == SYM_INTERNAL, sym==NULL )
; - CreateProto ( state == SYM_EXTERNAL )
; - ExterndefDirective ( state == SYM_EXTERNAL )
; - ExternDirective ( state == SYM_EXTERNAL )
; - TypedefDirective ( state == SYM_TYPE, sym==NULL )

    B equ <byte ptr>

CreateProc proc __ccall uses rsi rdi sym:ptr asym, name:string_t, state:sym_state

    ldr rax,sym
    .if ( rax == NULL )
        mov rdi,name
        .if ( B[rdi] )
            SymCreate( rdi )
        .else
            SymAlloc( rdi )
        .endif
        mov sym,rax
    .else
        .if ( [rax].asym.state == SYM_UNDEFINED )
            lea rcx,SymTables[TAB_UNDEF*symbol_queue]
        .else
            lea rcx,SymTables[TAB_EXT*symbol_queue]
        .endif
        sym_remove_table( rcx, rax )
    .endif

    mov rdi,sym
    .if ( rdi )
        mov [rdi].asym.state,state
        .if ( state != SYM_INTERNAL )
            mov [rdi].asym.segoffsize,ModuleInfo.Ofssize
        .endif
        mov [rdi].dsym.procinfo,LclAlloc( sizeof( proc_info ) )
if 0 ; zero alloc..
        xor ecx,ecx
        mov [rax].proc_info.regslist,ecx
        mov [rax].proc_info.paralist,ecx
        mov [rax].proc_info.locallist,ecx
        mov [rax].proc_info.labellist,ecx
        mov [rax].proc_info.parasize,ecx
        mov [rax].proc_info.localsize,ecx
        mov [rax].proc_info.prologuearg,ecx
        mov [rax].proc_info.flags,cl
endif
        .switch ( [rdi].asym.state )
        .case SYM_INTERNAL

            ; v2.04: don't use sym_add_table() and thus
            ; free the <next> member field!

            .if ( SymTables[TAB_PROC*symbol_queue].head == NULL )
                mov SymTables[TAB_PROC*symbol_queue].head,rdi
            .else
                mov rcx,SymTables[TAB_PROC*symbol_queue].tail
                mov [rcx].dsym.nextproc,rdi
            .endif
            mov SymTables[TAB_PROC*symbol_queue].tail,rdi
            inc procidx
            .if ( Options.line_numbers )
                mov [rdi].asym.debuginfo,LclAlloc( sizeof( debug_info ) )
                get_curr_srcfile()
                mov rdx,[rdi].asym.debuginfo
                mov [rdx].debug_info.file,ax
            .endif
            .endc
        .case SYM_EXTERNAL
            or [rdi].asym.sflags,S_WEAK
            sym_add_table( &SymTables[TAB_EXT*symbol_queue], rdi )
            .endc
        .endsw
    .endif
    .return( rdi )

CreateProc endp


; delete a PROC item

DeleteProc proc __ccall uses rsi rdi p:ptr dsym

    ldr rdi,p
    .if ( [rdi].asym.state == SYM_INTERNAL )

        mov rsi,[rdi].dsym.procinfo

        ; delete all local symbols ( params, locals, labels )

        .for ( rdi = [rsi].labellist : rdi : )

            mov rsi,[rdi].dsym.nextll
            SymFree( rdi )
            mov rdi,rsi
        .endf
    .endif
    ret

DeleteProc endp


; PROC directive.

ProcDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local sym:ptr dsym
  local ofs:uint_t
  local name:string_t
  local oldpubstate:int_t
  local is_global:int_t
  local p:ptr proc_info

    ldr rbx,tokenarray
    ldr ecx,i

    .if ( ecx != 1 )
        imul ecx,ecx,asm_tok
        .return( asmerr( 2008, [rbx+rcx].string_ptr ) )
    .endif

    ; v2.04b: check was missing

    .if ( CurrSeg == NULL )

        ; v2.30.06 - struct proto's ...

        .if ( Parse_Pass == PASS_1 )
            .return( asmerr( 2034 ) )
        .endif
        .return( NOT_ERROR )
    .endif

    mov name,[rbx].string_ptr
    add rbx,asm_tok
    mov rdi,CurrProc
    .if ( rdi != NULL )

        ; this is not needed for JWasm, but Masm will reject nested
        ; procs if there are params, locals or used registers.

        mov rsi,[rdi].dsym.procinfo
        .if ( [rsi].paralist ||
              [rsi].flags & PROC_ISFRAME ||
              [rsi].locallist ||
              [rsi].regslist )
            .return( asmerr( 2144, name ) )
        .endif

        ; nested procs ... push currproc on a stack

        push_proc( rdi )
    .endif


    .if ( ModuleInfo.procalign )
        AlignCurrOffset( ModuleInfo.procalign )
    .endif

    inc i ; go past PROC
    add rbx,asm_tok

    mov sym,SymSearch( name )

    .if ( Parse_Pass == PASS_1 )

        mov oldpubstate,FALSE
        .if ( rax && [rax].asym.flags & S_ISPUBLIC )
            inc oldpubstate
        .endif
        .if ( rax == NULL || [rax].asym.state == SYM_UNDEFINED )
            mov sym,CreateProc( rax, name, SYM_INTERNAL )
            mov is_global,FALSE
        .elseif ( [rax].asym.state == SYM_EXTERNAL && [rax].asym.sflags & S_WEAK )

            ; PROTO or EXTERNDEF item

            mov is_global,TRUE
            .if ( [rax].asym.flags & S_ISPROC )

                ; don't create the procinfo extension; it exists already

                inc procidx ; v2.04: added
                .if ( Options.line_numbers )
                    mov rdi,LclAlloc( sizeof( debug_info ) )
                    mov rcx,sym
                    mov [rcx].asym.debuginfo,rdi
                    mov [rdi].debug_info.file,get_curr_srcfile()
                .endif
            .else

                ; it's a simple EXTERNDEF. Create a PROC item!
                ; this will be SYM_INTERNAL
                ; v2.03: don't call dir_free(), it'll clear field Ofssize

                mov sym,CreateProc( sym, name, SYM_INTERNAL )
            .endif
        .else

            ; Masm won't reject a redefinition if "certain" parameters
            ; won't change. However, in a lot of cases one gets "internal assembler error".
            ; Hence this "feature" isn't active in jwasm.

            mov rcx,sym
            .return( asmerr( 2005, [rcx].asym.name ) )
        .endif
        mov rdi,sym
        SetSymSegOfs( rdi )
        SymClearLocal()

        ; v2.11: added. Note that fpo flag is only set if there ARE params!

        mov rsi,[rdi].dsym.procinfo
        movzx ecx,ModuleInfo.Ofssize
        lea rdx,ModuleInfo
        mov ecx,[rdx].module_info.basereg[rcx*4]
        mov [rsi].basereg,cx

        ; CurrProc must be set, it's used inside SymFind() and SymLCreate()!

        mov CurrProc,rdi
        tsprintf(&strFUNC, "\"%s\"", [rdi].asym.name)
        .ifd ( ParseProc( rdi, i, tokenarray, TRUE, ModuleInfo.langtype ) == ERROR )

            mov CurrProc,NULL
            mov strFUNC,0
           .return( ERROR )
        .endif

        ; v2.04: added

        .if ( is_global && Options.masm8_proc_visibility )
            or [rdi].asym.flags,S_ISPUBLIC
        .endif

        ; if there was a PROTO (or EXTERNDEF name:PROTO ...),
        ; change symbol to SYM_INTERNAL!

        .if ( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.flags & S_ISPROC )
            sym_ext2int( rdi )

            ; v2.11: added ( may be better to call CreateProc() - currently not possible )

            .if ( SymTables[TAB_PROC*symbol_queue].head == NULL )
                mov SymTables[TAB_PROC*symbol_queue].head,rdi
            .else
                mov rcx,SymTables[TAB_PROC*symbol_queue].tail
                mov [rcx].dsym.nextproc,rdi
            .endif
            mov SymTables[TAB_PROC*symbol_queue].tail,rdi
        .endif

        ; v2.11: sym->isproc is set inside ParseProc()
        ; v2.11: Note that fpo flag is only set if there ARE params ( or locals )!

        mov rcx,CurrProc
        mov rsi,[rcx].dsym.procinfo
        movzx ecx,[rsi].basereg
        .if ( [rsi].paralist && GetRegNo( ecx ) == 4 )
            or [rsi].flags,PROC_FPO
        .endif
        .if ( [rdi].asym.flags & S_ISPUBLIC && oldpubstate == FALSE )
            AddPublicData( rdi )
        .endif

        ; v2.04: add the proc to the list of labels attached to curr segment.
        ; this allows to reduce the number of passes (see fixup.asm)

        mov rcx,CurrSeg
        mov rdx,[rcx].dsym.seginfo
        mov [rdi].dsym.next,[rdx].seg_info.label_list
        mov [rdx].seg_info.label_list,rdi

    .else

        ; v2.30.06 - struct proto's ...

        mov rdi,sym
        .if ( rdi == NULL )
            .return( NOT_ERROR )
        .endif

        inc procidx
        or  [rdi].asym.flags,S_ISDEFINED
        SymSetLocal( rdi )

        ; it's necessary to check for a phase error here
        ; as it is done in LabelCreate() and data_dir()!

        mov ecx,GetCurrOffset()
        .if ( ecx != [rdi].asym.offs )
            mov [rdi].asym.offs,ecx
            mov ModuleInfo.PhaseError,TRUE
        .endif
        mov CurrProc,rdi
        tsprintf(&strFUNC, "\"%s\"", [rdi].asym.name)

        ; check if the exception handler set by FRAME is defined

        mov rsi,[rdi].dsym.procinfo
        mov rcx,[rsi].exc_handler
        .if ( [rsi].flags & PROC_ISFRAME && rcx && [rcx].asym.state == SYM_UNDEFINED )
            asmerr( 2006, [rcx].asym.name )
        .endif
    .endif

    mov rcx,CurrProc
    mov rsi,[rcx].dsym.procinfo

    ; v2.11: init @ProcStatus - prologue not written yet, optionally set FPO flag

    mov ecx,PRST_PROLOGUE_NOT_DONE
    .if ( [rsi].flags & PROC_FPO )
        or ecx,PRST_FPO
    .endif
    mov ProcStatus,ecx
    mov StackAdj,0  ; init @StackBase to 0
    mov StackAdjHigh,0

    .if ( [rsi].flags & PROC_ISFRAME )
        mov endprolog_found,FALSE

        ; v2.11: clear all fields

        tmemset( &unw_info, 0, sizeof( unw_info ) )
        .if ( [rsi].exc_handler )
            unw_info.set_Flags(UNW_FLAG_FHANDLER)
        .endif
    .endif

    mov rcx,sym
    mov [rcx].asym.asmpass,Parse_Pass
    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif

    .if ( Options.line_numbers )
        mov edi,get_curr_srcfile()
        .if ( Options.debug_symbols == 4 )
            AddLinnumDataRef( edi, GetLineNumber() )
        .else
            xor eax,eax
            .if ( Options.output_format != OFORMAT_COFF )
                GetLineNumber()
            .endif
            AddLinnumDataRef( edi, eax )
        .endif
    .endif

    BackPatch( sym )
   .return( NOT_ERROR )

ProcDir endp


CopyPrototype proc __ccall uses rsi rdi p:ptr dsym, src:ptr dsym

    ldr rdi,p
    mov rsi,[rdi].dsym.procinfo
    mov rcx,src
    .if ( !( [rcx].asym.flags & S_ISPROC ) )
        .return( ERROR )
    .endif
    tmemcpy( rsi, [rcx].dsym.procinfo, sizeof( proc_info ) )
    mov rcx,src
    mov [rdi].asym.mem_type,[rcx].asym.mem_type
    mov [rdi].asym.langtype,[rcx].asym.langtype
    and [rdi].asym.flags,not S_ISPUBLIC
    .if ( [rcx].asym.flags & S_ISPUBLIC )
        or [rdi].asym.flags,S_ISPUBLIC
    .endif
    ;
    ; we use the PROTO part, not the TYPE part
    ;
    mov [rdi].asym.segoffsize,[rcx].asym.segoffsize
    or  [rdi].asym.flags,S_ISPROC
    mov [rsi].paralist,NULL

    mov rdx,[rcx].dsym.procinfo
    .for ( rdi = [rdx].proc_info.paralist: rdi : rdi = [rdi].dsym.nextparam )
        tmemcpy( LclAlloc( sizeof( dsym ) ), rdi, sizeof( dsym ) )
        mov [rax].dsym.nextparam,NULL
        .if ( ![rsi].paralist )
            mov [rsi].paralist,rax
        .else
            .for ( rcx = [rsi].paralist : [rcx].dsym.nextparam: rcx = [rcx].dsym.nextparam )
            .endf
            mov [rcx].dsym.nextparam,rax
        .endif
    .endf
    .return( NOT_ERROR )

CopyPrototype endp

;
; for FRAME procs, write .pdata and .xdata SEH unwind information
;

WriteSEHData proc __ccall private uses rsi rdi rbx p:ptr dsym

   .new xdata:ptr dsym
   .new segname:string_t = ".xdata"
   .new i:int_t
   .new simplespec:int_t
   .new olddotname:uchar_t
   .new xdataofs:uint_t = 0
   .new segnamebuff[12]:char_t
   .new buffer[128]:char_t

    ldr rdi,p
    .if ( endprolog_found == FALSE )
        asmerr( 3007, [rdi].asym.name )
    .endif
    .if ( unw_segs_defined )
        AddLineQueueX("%s %r", segname, T_SEGMENT )
    .else
        AddLineQueueX(
            "%s %r align(%u) flat read 'DATA'\n"
            "$xdatasym label near", segname, T_SEGMENT, 8 )
    .endif
    mov xdataofs,0
    mov xdata,SymSearch( segname )
    .if ( rax )
        ;
        ; v2.11: changed offset to max_offset.
        ; However, value structinfo.current_loc might even be better.
        ;
        mov xdataofs,[rax].asym.max_offset
    .endif

    ;
    ; write the .xdata stuff (a UNWIND_INFO entry )
    ; v2.11: 't'-suffix added to ensure the values are correct if radix is != 10.
    ;
    mov ecx,unw_info.Flags()
    mov edx,unw_info.FrameRegister()
    AddLineQueueX( "db %ut + (0%xh shl 3), %ut, %ut, 0%xh + (0%xh shl 4)",
            UNW_VERSION, ecx, unw_info.SizeOfProlog,
            unw_info.CountOfCodes, edx, unw_info.FrameOffset() )

    .if ( unw_info.CountOfCodes )

       .new pfx:string_t = "dw"
        mov buffer[0],NULLC

        ; write the codes from right to left

        movzx esi,unw_info.CountOfCodes
        .for ( rdi = &buffer : esi : esi-- )

            lea rbx,[rdi+tstrlen(rdi)]
            lea rcx,unw_code
            mov rdx,rsi
            tsprintf( rbx, "%s 0%xh", pfx, [rcx+rdx*2-2].UNWIND_CODE.FrameOffset )

            mov pfx,&T(",")
            .if ( esi == 1 || tstrlen( rdi ) > 72 )
                AddLineQueue( rdi )
                mov byte ptr [rdi],NULLC
                mov pfx,&T("dw")
            .endif
        .endf
    .endif

    ; make sure the unwind codes array has an even number of entries

    AddLineQueue( "ALIGN 4" )

    mov rdi,p
    mov rsi,[rdi].dsym.procinfo
    .if ( [rsi].exc_handler )
        mov rcx,[rsi].exc_handler
        AddLineQueueX(
            "dd IMAGEREL %s\n"
            "ALIGN 8", [rcx].asym.name )
    .endif
    AddLineQueueX( "%s ENDS", segname )

    ;
    ; v2.07: ensure that .pdata items are sorted
    ;

    SimGetSegName( SIM_CODE )
    mov rcx,[rdi].asym.segm

    .ifd ( !tstrcmp( rax, [rcx].asym.name ) )

        mov segname,&T(".pdata")
        mov al,unw_segs_defined
        and eax,1
        mov simplespec,eax
        mov unw_segs_defined,3
    .else
        mov segname,segnamebuff
        tsprintf( segname, ".pdata$%04u", GetSegIdx( [rdi].asym.segm ) )
        mov simplespec,0
        or  unw_segs_defined,2
    .endif

    .if ( simplespec )
        AddLineQueueX( "%s SEGMENT", segname )
    .else
        AddLineQueueX( "%s SEGMENT ALIGN(4) flat read 'DATA'", segname )
    .endif

    ; write the .pdata stuff ( type IMAGE_RUNTIME_FUNCTION_ENTRY )

    AddLineQueueX(
        "dd IMAGEREL %s, IMAGEREL %s+0%xh, IMAGEREL $xdatasym+0%xh\n"
        "%s ENDS", [rdi].asym.name, [rdi].asym.name, [rdi].asym.total_size, xdataofs, segname )
    mov olddotname,ModuleInfo.dotname
    mov ModuleInfo.dotname,TRUE ; set OPTION DOTNAME because .pdata and .xdata
    RunLineQueue()
    mov ModuleInfo.dotname,olddotname
    ret

WriteSEHData endp

;
; close a PROC
;
SetLocalOffsets proto __ccall :ptr proc_info

ProcFini proc __ccall private uses rsi rdi p:ptr dsym

    ;
    ; v2.06: emit an error if current segment isn't equal to
    ; the one of the matching PROC directive. Close the proc anyway!
    ;
    ldr rdi,p
    mov rax,[rdi].asym.segm

    .if ( CurrSeg == rax )

        mov ecx,GetCurrOffset()
        sub ecx,[rdi].asym.offs
        mov [rdi].asym.total_size,ecx

    .else

        asmerr( 1010, [rdi].asym.name )
        mov rdx,CurrSeg
        mov rcx,[rdx].asym.segm
        mov ecx,[rcx].asym.offs
        sub ecx,[rdi].asym.offs
        mov [rdi].asym.total_size,ecx
    .endif
    ;
    ; v2.03: for W3+, check for unused params and locals
    ;
    mov rsi,[rdi].dsym.procinfo
    .if ( Options.warning_level > 2 && Parse_Pass == PASS_1 )

        .for ( rdi = [rsi].paralist: rdi: rdi = [rdi].dsym.nextparam )
            .if ( !( [rdi].asym.flags & S_USED ) )
                asmerr( 6004, [rdi].asym.name )
            .endif
        .endf

        .for ( rdi = [rsi].locallist: rdi: rdi = [rdi].dsym.nextlocal )
            .if ( !( [rdi].asym.flags & S_USED ) )
                asmerr( 6004, [rdi].asym.name )
            .endif
        .endf
    .endif
    ;
    ; save stack space reserved for INVOKE if OPTION WIN64:2 is set
    ;
    .if ( Parse_Pass == PASS_1 &&
         ( ModuleInfo.fctype == FCT_WIN64 ||
           ModuleInfo.fctype == FCT_VEC64 ||
           ModuleInfo.fctype == FCT_ELF64 ) && ; v2.28: added
         ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        mov rcx,sym_ReservedStack
        mov ecx,[rcx].asym.value
        mov [rsi].ReservedStack,ecx
        .if ( [rsi].flags & PROC_FPO )
            .for ( rdi = [rsi].locallist: rdi: rdi = [rdi].dsym.nextlocal )
                add [rdi].asym.offs,ecx
            .endf
            .for ( rdi = [rsi].paralist: rdi: rdi = [rdi].dsym.nextparam )
                add [rdi].asym.offs,ecx
            .endf
        .endif
    .endif
    ;
    ; create the .pdata and .xdata stuff
    ;
    .if ( [rsi].flags & PROC_ISFRAME )
        LstSetPosition() ; needed if generated code is done BEFORE the line is listed
        WriteSEHData( p )
    .endif
    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif
    ;
    ; create the list of locals
    ;
    .if ( Parse_Pass == PASS_1 )
        ;
        ; in case the procedure is empty, init addresses of local variables ( for proper listing )
        ;
        .if ( ProcStatus & PRST_PROLOGUE_NOT_DONE )
            mov rcx,CurrProc
            mov rcx,[rcx].dsym.procinfo
            SetLocalOffsets( rcx )
        .endif
        SymGetLocal( CurrProc )
    .endif

    mov CurrProc,pop_proc()
    .if ( CurrProc )
        tsprintf(&strFUNC, "\"%s\"", [rax].asym.name)
        SymSetLocal( CurrProc ) ; restore local symbol table
    .else
        mov strFUNC,0
    .endif
    mov ProcStatus,0 ; in case there was an empty PROC/ENDP pair
    ret

ProcFini endp

;
; ENDP directive
;

EndpDir proc __ccall uses rbx i:int_t, tokenarray:ptr asm_tok

  local buffer[128]:char_t

    ldr rbx,tokenarray
    .if ( i != 1 || [rbx+2*asm_tok].token != T_FINAL )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [rbx+rcx].tokpos ) )
    .endif

    ; v2.30: .return without RET ?

    .if ( ModuleInfo.RetStack )

        AddLineQueue( "org $ - 2" ) ; skip the last jump
        AddLineQueue( "ret" )
        RunLineQueue()
    .endif

    ; v2.10: "+ 1" added to CurrProc->sym.name_size

    mov rcx,CurrProc
    .if ( rcx )

        mov edx,[rcx].asym.name_size
        inc edx
        .if ( SymCmpFunc( [rcx].asym.name, [rbx].string_ptr, edx ) == 0 )
            ProcFini( CurrProc )
            mov ecx,1
        .else
            xor ecx,ecx
        .endif
    .endif
    .if ( ecx == 0 )
        .return( asmerr( 1010, [rbx].string_ptr ) )
    .endif
    .return( NOT_ERROR )

EndpDir endp

;
; handles win64 directives
; .allocstack
; .endprolog
; .pushframe
; .pushreg
; .savereg
; .savexmm128
; .setframe
;

ExcFrameDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

   .new opndx:expr
   .new token:int_t
   .new size:dword
   .new oldcodes:byte = unw_info.CountOfCodes
   .new reg:byte
   .new ofs:byte
   .new puc:ptr UNWIND_CODE

    mov rdi,CurrProc
    mov rbx,tokenarray.tokptr(i)

    ; v2.05: accept directives for windows only

    .if ( Options.output_format == OFORMAT_ELF ||
          Options.output_format == OFORMAT_OMF ||
          ModuleInfo.sub_format == SFORMAT_MZ )
        .return( asmerr( 3006, GetResWName( [rbx].tokval, NULL ) ) )
    .endif
    .if ( rdi == NULL || endprolog_found == TRUE )
        .return( asmerr( 3008 ) )
    .endif

    mov rsi,[rdi].dsym.procinfo
    .if ( !( [rsi].flags & PROC_ISFRAME ) )
        .return( asmerr( 3009 ) )
    .endif

    movzx ecx,unw_info.CountOfCodes
    lea rax,unw_code
    mov puc,&[rax+rcx*UNWIND_CODE]
    mov ecx,GetCurrOffset()
    sub ecx,[rdi].asym.offs
    mov ofs,cl
    mov token,[rbx].tokval
    inc i
    add rbx,asm_tok

    ; note: since the codes will be written from "right to left",
    ; the opcode item has to be written last!

    .switch ( token )
    .case T_DOT_ALLOCSTACK ; syntax: .ALLOCSTACK size
        .return .ifd ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )

        mov rbx,tokenarray.tokptr(i)
        mov rcx,opndx.sym
        .if ( opndx.kind == EXPR_ADDR && [rcx].asym.state == SYM_UNDEFINED )
            ; v2.11: allow forward references
        .elseif ( opndx.kind != EXPR_CONST )
            .return( asmerr( 2026 ) )
        .endif

        ; v2.11: check added

        .if ( opndx.hvalue )
            .return( EmitConstError( &opndx ) )
        .endif
        .if ( opndx.uvalue == 0 )
            .return( asmerr( 2090 ) )
        .endif
        .if ( opndx.value & 7 )
            .return( asmerr( 2189, opndx.value ) )
        .endif
        .if ( opndx.uvalue > 16*8 )
            .if ( opndx.uvalue >= 65536*8 )

                ; allocation size 512k - 4G-8
                ; v2.11: value is stored UNSCALED in 2 WORDs!

                mov edx,opndx.uvalue
                shr edx,16
                puc.set_FrameOffset(edx)
                add puc,UNWIND_CODE
                puc.set_FrameOffset(opndx.uvalue)
                add puc,UNWIND_CODE
                add unw_info.CountOfCodes,2
                puc.set_OpInfo(1)
            .else

                ; allocation size 128+8 - 512k-8

                mov edx,opndx.uvalue
                shr edx,3
                puc.set_FrameOffset(edx)
                add puc,UNWIND_CODE
                inc unw_info.CountOfCodes
                puc.set_OpInfo(0)
            .endif
            puc.set_UnwindOp(UWOP_ALLOC_LARGE)
        .else

            ; allocation size 8-128 bytes

            puc.set_UnwindOp(UWOP_ALLOC_SMALL)
            mov edx,opndx.uvalue
            sub edx,8
            shr edx,3
            puc.set_OpInfo(edx)
        .endif
        puc.set_CodeOffset(ofs)
        inc unw_info.CountOfCodes
        .endc
    .case T_DOT_ENDPROLOG ;; syntax: .ENDPROLOG
        mov ecx,GetCurrOffset()
        sub ecx,[rdi].asym.offs
        mov opndx.value,ecx
        .if ( ecx > 255 )
            .return( asmerr( 3010 ) )
        .endif
        mov unw_info.SizeOfProlog,opndx.uvalue
        mov endprolog_found,TRUE
        .endc
    .case T_DOT_PUSHFRAME ; syntax: .PUSHFRAME [code]
        puc.set_CodeOffset(ofs)
        puc.set_UnwindOp(UWOP_PUSH_MACHFRAME)
        puc.set_OpInfo(0)
        .if ( [rbx].token == T_ID )

            mov rcx,[rbx].string_ptr
            mov eax,[rcx]
            or  eax,0x20202020
            .if ( eax == 'edoc' && byte ptr [rcx+4] == 0 )
                puc.set_OpInfo(1)
                inc i
                add rbx,asm_tok
            .endif
        .endif
        inc unw_info.CountOfCodes
        .endc
    .case T_DOT_PUSHREG ; syntax: .PUSHREG r64
        mov ecx,GetValueSp( [rbx].tokval )
        and ecx,OP_R64
        .if ( [rbx].token != T_REG || !( ecx ) )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif
        puc.set_CodeOffset(ofs)
        puc.set_UnwindOp(UWOP_PUSH_NONVOL)
        puc.set_OpInfo(GetRegNo( [rbx].tokval ))
        inc unw_info.CountOfCodes
        inc i
        add rbx,asm_tok
        .endc
    .case T_DOT_SAVEREG    ; syntax: .SAVEREG r64, offset
    .case T_DOT_SAVEXMM128 ; syntax: .SAVEXMM128 xmmreg, offset
    .case T_DOT_SETFRAME   ; syntax: .SETFRAME r64, offset
        .if ( [rbx].token != T_REG )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif
        .if ( token == T_DOT_SAVEXMM128 )
            .if ( !( GetValueSp( [rbx].tokval ) & OP_XMM ) )
                .return( asmerr( 2008, [rbx].string_ptr ) )
            .endif
        .else
            .if ( !( GetValueSp( [rbx].tokval ) & OP_R64 ) )
                .return( asmerr( 2008, [rbx].string_ptr ) )
            .endif
        .endif
        mov reg,GetRegNo( [rbx].tokval )

        .if ( token == T_DOT_SAVEREG )
            mov size,8
        .else
            mov size,16
        .endif

        inc i
        add rbx,asm_tok
        .if ( [rbx].token != T_COMMA )
            .return( asmerr(2008, [rbx].string_ptr ) )
        .endif
        inc i
        .return .ifd ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )

        mov rbx,tokenarray.tokptr(i)
        mov rcx,opndx.sym
        .if ( opndx.kind == EXPR_ADDR && [rcx].asym.state == SYM_UNDEFINED )
            ; v2.11: allow forward references
        .elseif ( opndx.kind != EXPR_CONST )
            .return( asmerr( 2026 ) )
        .endif
        mov eax,size
        dec eax
        .if ( opndx.value & eax )
            .return( asmerr( 2189, size ) )
        .endif
        .switch ( token )
        .case T_DOT_SAVEREG
            puc.set_OpInfo(reg)
            imul ecx,size,65536
            .if ( opndx.value > ecx )
                mov ecx,opndx.value
                shr ecx,19
                puc.set_FrameOffset( ecx )
                add puc,UNWIND_CODE
                mov ecx,opndx.value
                shr ecx,3
                puc.set_FrameOffset( ecx )
                add puc,UNWIND_CODE
                puc.set_UnwindOp(UWOP_SAVE_NONVOL_FAR)
                add unw_info.CountOfCodes,3
            .else
                mov ecx,opndx.value
                shr ecx,3
                puc.set_FrameOffset( ecx )
                add puc,UNWIND_CODE
                puc.set_UnwindOp(UWOP_SAVE_NONVOL)
                add unw_info.CountOfCodes,2
            .endif
            puc.set_CodeOffset(ofs)
            puc.set_OpInfo(reg)
            .endc
        .case T_DOT_SAVEXMM128
            imul ecx,size,65536
            .if ( opndx.value > ecx )
                mov ecx,opndx.value
                shr ecx,20
                puc.set_FrameOffset( ecx )
                add puc,UNWIND_CODE
                mov ecx,opndx.value
                shr ecx,4
                puc.set_FrameOffset( ecx )
                add puc,UNWIND_CODE
                puc.set_UnwindOp(UWOP_SAVE_XMM128_FAR)
                add unw_info.CountOfCodes,3
            .else
                mov ecx,opndx.value
                shr ecx,4
                puc.set_FrameOffset( ecx )
                add puc,UNWIND_CODE
                puc.set_UnwindOp(UWOP_SAVE_XMM128)
                add unw_info.CountOfCodes,2
            .endif
            puc.set_CodeOffset(ofs)
            puc.set_OpInfo(reg)
            .endc
        .case T_DOT_SETFRAME
            .if ( opndx.uvalue > 240 )
                .return( EmitConstError( &opndx ) )
            .endif
            unw_info.set_FrameRegister(reg)
            mov edx,opndx.uvalue
            shr edx,4
            unw_info.set_FrameOffset(edx)
            puc.set_CodeOffset(ofs)
            puc.set_UnwindOp(UWOP_SET_FPREG)
            puc.set_OpInfo(reg)
            inc unw_info.CountOfCodes
            .endc
        .endsw
        .endc
    .endsw
    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif

    ; v2.11: check if the table of codes has been exceeded

    .if ( oldcodes > unw_info.CountOfCodes )
        .return( asmerr( 3011 ) )
    .endif
    .return( NOT_ERROR )

ExcFrameDirective endp

;
; see if there are open procedures.
; called when the END directive has been found.
;

ProcCheckOpen proc __ccall uses rdi

    mov rdi,CurrProc
    .while ( rdi != NULL )
        asmerr( 1010, [rdi].asym.name )
        ProcFini( rdi )
        mov rdi,CurrProc
    .endw
    ret

ProcCheckOpen endp


write_userdef_prologue proc __ccall private uses rsi rdi rbx tokenarray:ptr asm_tok

   .new info:ptr proc_info
   .new len:int_t
   .new i:int_t
   .new p:string_t
   .new is_exitm:int_t
   .new dir:ptr dsym
   .new regs:ptr word
   .new reglst[128]:char_t
   .new buffer[MAX_LINE_LEN]:char_t
   .new flags:int_t

    .if ( Parse_Pass > PASS_1 && UseSavedState )
        .return( NOT_ERROR )
    .endif

    mov rdi,CurrProc
    mov rsi,[rdi].dsym.procinfo
    movzx ebx,[rdi].asym.langtype ; set bits 0-2
    mov info,rsi

    ; to be compatible with ML64, translate FASTCALL to 0 (not 7)

    .if ( ebx == LANG_FASTCALL && ModuleInfo.fctype == FCT_WIN64 )
        mov ebx,0
    .endif

    ; set bit 4 if the caller restores (E)SP

    .if ( ebx == LANG_C || ebx == LANG_SYSCALL || ebx == LANG_FASTCALL )
        or ebx,0x10
    .endif

    ; set bit 5 if proc is far
    ; set bit 6 if proc is private
    ; v2.11: set bit 7 if proc is export

    .if ( [rdi].asym.mem_type == MT_FAR )
        or ebx,0x20
    .endif
    .if ( !( [rdi].asym.flags & S_ISPUBLIC ) )
        or ebx,0x40
    .endif
    .if ( [rsi].flags & PROC_ISEXPORT )
        or ebx,0x80
    .endif
    mov flags,ebx

    mov dir,SymSearch( ModuleInfo.proc_prologue )
    .if ( eax == NULL || [rax].asym.state != SYM_MACRO || !( [rax].asym.mac_flag & M_ISFUNC ) )
        .return( asmerr( 2120 ) )
    .endif

    ; if -EP is on, emit "prologue: none"

    .if ( Options.preprocessor_stdout )
        tprintf( "option prologue:none\n" )
    .endif

    lea rdi,reglst
    mov rsi,[rsi].regslist
    .if ( rsi )
        movzx ebx,word ptr [rsi]
        .for ( rsi += 2: ebx: ebx--, rsi += 2 )
            movzx ecx,word ptr [rsi]
            GetResWName( ecx, rdi )
            add rdi,tstrlen( rdi )
            .if ( ebx > 1 )
                mov byte ptr [rdi],','
                inc rdi
            .endif
        .endf
    .endif
    mov byte ptr [rdi],NULLC

    mov rsi,info
    mov rdi,CurrProc

    ; v2.07: make this work with radix != 10
    ; leave a space at pos 0 of buffer, because the buffer is used for
    ; both macro arguments and EXITM return value.

    mov rcx,[rsi].prologuearg
    .if ( !rcx )
        lea rcx,@CStr("")
    .endif

    tsprintf( &buffer," (%s, 0%XH, 0%XH, 0%XH, <<%s>>, <%s>)",
             [rdi].asym.name, flags, [rsi].parasize, [rsi].localsize, &reglst, rcx )

    mov ebx,Token_Count
    inc ebx
    mov Token_Count,Tokenize( &buffer, ebx, tokenarray, TOK_RESCAN )

    RunMacro( dir, ebx, tokenarray, &buffer, 0, &is_exitm )
    dec ebx
    mov Token_Count,ebx

    .if ( Parse_Pass == PASS_1 )

        mov ebx,_atoqw( &buffer )
        sub ebx,[rsi].localsize

        .for ( rdi = [rsi].locallist: rdi: rdi = [rdi].dsym.nextlocal )
            sub [rdi].asym.offs,ebx
        .endf
    .endif
    .return ( NOT_ERROR )

write_userdef_prologue endp


; OPTION WIN64:1 - save up to 4 register parameters for WIN64 fastcall
; v2.27 - save up to 6 register parameters for WIN64 vectorcall
; v2.30 - reverse direction of args + vectorcall stack 8/16

win64_MoveRegParam proc __ccall private uses rsi rdi rbx i:int_t, size:int_t, param:ptr dsym

  local langtype:byte

    mov rcx,CurrProc
    mov langtype,[rcx].asym.langtype
    xor esi,esi

    mov rdi,param
    mov al,[rdi].asym.mem_type
    .if ( al == MT_TYPE )
        mov rdx,[rdi].asym.type
        mov al,[rdx].asym.mem_type
    .endif

    mov ecx,i
    lea edx,[rcx+T_XMM0]
    xor ebx,ebx

    .if ( al & MT_FLOAT || al == MT_YWORD ||
          ( langtype == LANG_VECTORCALL && al == MT_OWORD ) )

        .if ( al == MT_REAL4 || al == MT_REAL2 )
            mov esi,T_MOVD
        .elseif ( al == MT_REAL8 )
            mov esi,T_MOVQ
        .elseif ( [rdi].asym.total_size <= 16 )
            mov esi,T_MOVAPS
        .elseif ( [rdi].asym.total_size == 32 )
            mov esi,T_VMOVUPS
            lea edx,[rcx+T_YMM0]
        .elseif ( [rdi].asym.total_size == 64 )
            mov esi,T_VMOVUPS
            lea edx,[rcx+T_ZMM0]
        .endif

    .elseif ( ecx < 4 )
if 1
        lea rdi,ms64_regs
        mov edx,[rdi+rcx*4]
else
        lea rdi,ms64_regs
        mov esi,[rdi+rcx*4]
        .switch al
        .case MT_BYTE
        .case MT_SBYTE
            mov esi,get_register(esi, 1)
           .endc
        .case MT_WORD
        .case MT_SWORD
            mov esi,get_register(esi, 2)
           .endc
        .case MT_DWORD
        .case MT_SDWORD
            mov esi,get_register(esi, 4)
           .endc
        .case MT_OWORD
            .if ( langtype != LANG_VECTORCALL )
                mov ebx,[rdi+rcx*4+4]
                inc i
            .endif
        .endsw
        mov edx,esi
        mov ecx,i
endif
        mov esi,T_MOV
        .if ( al == MT_OWORD && langtype != LANG_VECTORCALL )
            mov ebx,[rdi+rcx*4+4]
            inc i
        .endif
    .endif

    .if ( esi )

        imul ecx,size
        lea edi,[rcx+8]
        AddLineQueueX( "%r [rsp+%u], %r", esi, edi, edx )
        .if ( ebx )
            add edi,8
            AddLineQueueX( "%r [rsp+%u], %r", esi, edi, ebx )
        .endif
    .endif
    .return( i )

win64_MoveRegParam endp


win64_GetRegParams proc __ccall private uses rsi rdi rbx varargs:ptr int_t, size:ptr inr_t, param:ptr dsym

    ldr rsi,size
    ldr rdi,param
    mov rcx,CurrProc
    mov cl,[rcx].asym.langtype

    .if ( cl == LANG_VECTORCALL )
        mov dword ptr [rsi],16
    .else
        mov dword ptr [rsi],8
    .endif
    mov rdx,varargs
    .if ( rdi && [rdi].asym.sflags & S_ISVARARG )
        mov dword ptr [rdx],1
        .return 4
    .endif
    mov dword ptr [rdx],0
    .for ( ebx = 0: rdi: rdi = [rdi].dsym.nextparam )
        mov eax,[rsi]
        .if ( [rdi].asym.total_size > eax )
            .switch ( [rdi].asym.mem_type )  ; limit to float/vector..
            .case MT_REAL10 ; v2.32.32 - REAL10
            .case MT_OWORD
            .case MT_REAL16
                mov dword ptr [rsi],16
                .endc
            .case MT_YWORD
                mov dword ptr [rsi],32
                .endc
            .case MT_ZWORD
                mov dword ptr [rsi],64
                .endc
            .endsw
        .endif
        inc ebx
    .endf
    .return( ebx )

win64_GetRegParams endp


win64_SaveRegParams proc __ccall private uses rsi rdi rbx info:ptr proc_info

   .new size:int_t
   .new varargs:int_t
   .new params:int_t
   .new index:int_t
   .new maxregs:int_t = 4

    ldr rsi,info
    mov rdi,CurrProc
    .if ( [rdi].asym.langtype == LANG_VECTORCALL )
        mov maxregs,6
    .endif
    mov params,win64_GetRegParams( &varargs, &size, [rsi].paralist )

    .if ( varargs )
        .for ( eax = 0, rdi = [rsi].paralist : rdi && eax < ebx :
                rdi = [rdi].dsym.nextparam, eax++ )
        .endf
        mov varargs,eax
    .endif

    .for ( index = 0, ebx = 0 : ebx < params : ebx++, index++ )
        ;
        ; Reverse order from 0 to n
        ;
        .for ( rdi = [rsi].paralist, ecx = params, ecx -= ebx, ecx-- : ecx : ecx-- )

            .break .if ( ecx <= varargs )
            mov rdi,[rdi].dsym.nextparam
        .endf
        ;
        ; __int128 "eats" 2 registers
        ;
        .if ( index < maxregs )

            ; v2.05: save XMMx if type is float/double

            .if ( !( [rdi].asym.sflags & S_ISVARARG ) )

                .if ( Parse_Pass == PASS_1 && size >= 16 ) ; v2.30 - update param offset

                    mov eax,size
                    mul ebx
                    add eax,16
                    mov [rdi].asym.offs,eax
                .endif

                .if ( [rdi].asym.flags & S_USED || varargs || Parse_Pass == PASS_1 )

                    mov index,win64_MoveRegParam( index, size, rdi )
                .endif

            .elseif ( ebx < 4 )  ; v2.09: else branch added

                mov eax,size
                mul ebx
                add eax,8
                lea rcx,ms64_regs

                AddLineQueueX( "mov [rsp+%u], %r", eax, [rcx+rbx*4] )
            .endif

        .elseif ( Parse_Pass == PASS_1 && !( [rdi].asym.sflags & S_ISVARARG ) && size >= 16 )

            mov eax,size
            mul ebx
            add eax,16
            mov [rdi].asym.offs,eax
        .endif
    .endf
    ret

win64_SaveRegParams endp


push_user_registers proc __ccall private uses rsi rdi rbx list:string_t, useframe:int_t, offs:ptr int_t

   .new cntxmm:int_t = 0
    ldr rsi,list
    .if ( rsi )

        lodsw
        movzx ebx,ax

        .for ( : ebx : ebx--, rsi += 2 )

            movzx edi,word ptr [rsi]
            .if ( GetValueSp( edi ) & OP_XMM )

                inc cntxmm
            .else

                mov rcx,offs
                movzx eax,ModuleInfo.Ofssize
                shl eax,2
                add [rcx],eax

                AddLineQueueX( "push %r", edi )

                .if ( useframe )

                    mov cl,GetRegNo( edi )
                    mov eax,1
                    shl eax,cl
                    .if ( ax & win64_nvgpr )
                        AddLineQueueX( "%r %r", T_DOT_PUSHREG, edi )
                    .endif
                .endif
            .endif
        .endf
    .endif
    .return( cntxmm )

push_user_registers endp


; Use the same logic for prologue/epilogue..

use_cstack proc private

    xor eax,eax
    .if ( ModuleInfo.xflag & OPT_CSTACK &&
          ( ModuleInfo.Ofssize == USE64 ||
            ( ModuleInfo.Ofssize == USE32 &&
              ( cl == LANG_STDCALL || cl == LANG_C || cl == LANG_SYSCALL )
            ) ) )
        inc eax
    .endif
    ret

use_cstack endp

use_sysstack proc private

    xor eax,eax
    .if ( ModuleInfo.Ofssize == USE64 &&
          cl == LANG_SYSCALL &&
          [rsi].paralist &&
          ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
        inc eax
    .endif
    ret

use_sysstack endp


; write PROC prologue
; this is to be done after the LOCAL directives
; and *before* any real instruction
;
; prolog code timings
;
;                                                  best result
;               size  86  286  386  486  P     86  286  386  486  P
; push bp       2     11  3    2    1    1
; mov bp,sp     2     2   2    2    1    1
; sub sp,immed  4     4   3    2    1    1
;              -----------------------------
;               8     17  8    6    3    3     x   x    x    x    x
;
; push ebp      2     -   -    2    1    1
; mov ebp,esp   2     -   -    2    1    1
; sub esp,immed 6     -   -    2    1    1
;              -----------------------------
;               10    -   -    6    3    3              x    x    x
;
; enter imm,0   4     -   11   10   14   11
;
; write prolog code
;

write_default_prologue proc __ccall private uses rsi rdi rbx

   .new info:ptr proc_info
   .new regist:ptr word
   .new oldlinenumbers:byte
   .new ppfmt:array_t
   .new cntxmm:int_t = 0
   .new cnt:int_t
   .new offs:int_t
   .new sysstack:int_t
   .new resstack:int_t = 0
   .new cstack:int_t
   .new leaf:int_t = 0
   .new usestack:int_t = 1
   .new argstack:int_t = 0
   .new argoffs:int_t = 0

    mov rdi,CurrProc
    mov rsi,[rdi].dsym.procinfo
    mov info,rsi
    mov cl,[rdi].asym.langtype
    mov cstack,use_cstack()
    mov sysstack,use_sysstack()


    .if ( ModuleInfo.Ofssize == USE64 && ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) &&
          ( cl == LANG_WATCALL || cl == LANG_FASTCALL || cl == LANG_VECTORCALL ) && Parse_Pass > PASS_1 )

        .if ( !( [rdi].asym.sflags & S_STKUSED ) && ![rsi].locallist )

            inc leaf

            .if ( !( [rdi].asym.sflags & ( S_ARGUSED or S_LOCALGPR ) ) &&
                  [rsi].localsize == 0 && [rsi].regslist == NULL )

                mov usestack,0
            .endif
        .endif
    .endif

    .if ( [rsi].flags & PROC_ISFRAME )

        .if ( ModuleInfo.frame_auto & 1 )

            ; win64 default prologue when PROC FRAME and
            ; OPTION FRAME:AUTO is set

            .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
                mov rcx,sym_ReservedStack
                mov resstack,[rcx].asym.value
            .endif

            .if ( ModuleInfo.win64_flags & W64F_SAVEREGPARAMS )
                win64_SaveRegParams( rsi )
            .endif

            ; PUSH RBP
            ; .PUSHREG RBP
            ; MOV RBP, RSP
            ; .SETFRAME RBP, 0

            ; Push the registers

            .if ( cstack == 1 )

                mov rsi,[rsi].regslist
                .if ( rsi )

                    mov offs,0
                    mov cntxmm,push_user_registers( rsi, 1, &offs )

                    mov rsi,info
                    .for ( rdi = [rsi].paralist: rdi: rdi = [rdi].dsym.nextparam )
                        .break .if ( ![rdi].dsym.nextparam )
                    .endf

                    .if ( rdi )

                        ; v2.23 - skip adding if stackbase is not EBP

                        movzx ecx,ModuleInfo.Ofssize
                        lea rdx,ModuleInfo
                        mov ecx,[rdx].module_info.basereg[rcx*4]

                        .if ( ( [rdi].asym.offs == 8 && ecx == T_EBP ) ||
                              ( [rdi].asym.offs == 16 && ecx == T_RBP ) )

                            .for ( rdi = [rsi].paralist: rdi: rdi = [rdi].dsym.nextparam )

                                .if ( [rdi].asym.state != SYM_TMACRO )
                                    add [rdi].asym.offs,offs
                                .endif
                            .endf
                        .endif
                    .endif
                .endif
            .endif

            ; info->locallist tells whether there are local variables ( info->localsize doesn't! )

            mov rsi,info
            .if ( [rsi].flags & PROC_FPO || ( [rsi].parasize == 0 && [rsi].locallist == NULL ) )

            .elseif( usestack )

                movzx ebx,[rsi].basereg
                AddLineQueueX(
                    "push %r\n"
                    "%r %r\n"
                    "mov %r, %r\n"
                    "%r %r, 0", ebx, T_DOT_PUSHREG, ebx, ebx, T_RSP, T_DOT_SETFRAME, ebx )
            .endif

            ; after the "push rbp", the stack is xmmword aligned

            ; Push the registers

            .if ( cstack == 0 )

                mov rsi,[rsi].regslist
                .if ( rsi )

                    mov offs,0
                    mov cntxmm,push_user_registers( rsi, 1, &offs )
                .endif
            .endif

            ; alloc space for local variables

            mov rsi,info
            mov ebx,[rsi].localsize
            add ebx,resstack

            .if ( ebx )

                ;
                ; SUB RSP, localsize
                ; .ALLOCSTACK localsize
                ;
if STACKPROBE
                .if ( Options.chkstack && ebx > 0x1000 )

                    AddLineQueueX(
                        "mov rax, %d\n"
                        "externdef _chkstk:PROC\n"
                        "call _chkstk\n"
                        "sub rsp, rax", ebx )

                .else
endif
                    AddLineQueueX( "sub rsp, %d", ebx )
if STACKPROBE
                .endif
endif
                AddLineQueueX( "%r %d", T_DOT_ALLOCSTACK, ebx )

                ; save xmm registers

                .if ( cntxmm )

                   .new i:int_t
                   .new cnt:int_t

                    imul ecx,cntxmm,16
                    mov eax,[rsi].localsize
                    sub eax,ecx
                    and eax,not (16-1)
                    mov i,eax

                    mov rsi,[rsi].regslist
                    lodsw
                    movzx ebx,ax

                    .for ( : ebx: ebx--, rsi += 2 )

                        movzx edi,word ptr [rsi]

                        .if ( GetValueSp( edi ) & OP_XMM )

                            .if ( resstack )

                                mov rcx,sym_ReservedStack
                                AddLineQueueX( "movdqa [%r+%u+%s], %r", T_RSP, i, [rcx].asym.name, edi )

                                mov cl,GetRegNo( edi )
                                mov eax,1
                                shl eax,cl
                                .if ( ax & win64_nvxmm )

                                    mov rcx,sym_ReservedStack
                                    AddLineQueueX( "%r %r, %u+%s", T_DOT_SAVEXMM128, edi, i, [rcx].asym.name )
                                .endif

                            .else

                                AddLineQueueX( "movdqa [%r+%u], %r", T_RSP, i, edi )
                                mov cl,GetRegNo( edi )
                                mov eax,1
                                shl eax,cl
                                .if ( ax & win64_nvxmm )
                                    AddLineQueueX( "%r %r, %u", T_DOT_SAVEXMM128, edi, i )
                                .endif
                            .endif
                            add i,16
                        .endif
                    .endf
                .endif
            .endif
            AddLineQueueX( "%r", T_DOT_ENDPROLOG )

            ; v2.11: linequeue is now run in write_default_prologue()
            ; v2.11: line queue is now run here

            jmp runqueue
        .endif
        .return( NOT_ERROR )
    .endif

    mov rsi,info
    .if ( ModuleInfo.Ofssize == USE64 &&
          ( ModuleInfo.fctype == FCT_WIN64 ||
            ModuleInfo.fctype == FCT_VEC64 ||
            ModuleInfo.fctype == FCT_ELF64 ) &&
          ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        mov rdi,CurrProc ; added v2.33.26
        mov rcx,sym_ReservedStack

        .if ( [rdi].asym.langtype == LANG_SYSCALL && Parse_Pass > PASS_1 )

            .if ( [rsi].flags & PROC_HAS_VARARG )
                ;
                ; tally up ReservedStack in case fastkall is
                ; invoked inside a syscall
                ;
                add [rcx].asym.value,208
            .endif
            .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
                ;
                ; reserve space for stack params used..
                ;
                mov al,[rdi].asym.sys_rcnt
                add al,[rdi].asym.sys_xcnt
                .if ( eax )
                    .for ( ebx = 8, eax = 0, rdx = [rsi].paralist : rdx : rdx = [rdx].dsym.nextparam )
                        .if ( [rdx].asym.flags & S_USED && [rdx].asym.flags & S_REGPARAM )

                            inc eax
                            .if ( bl < [rdx].asym.sys_size )
                                mov bl,[rdx].asym.sys_size
                            .endif
                        .endif
                    .endf
                    .if ( eax )

                        mov [rdi].asym.sys_size,bl
                        mul bl
                        add [rcx].asym.value,ROUND_UP( eax, 16 )
                        mov argstack,eax
                    .endif
                .endif
            .endif
        .endif
        mov resstack,[rcx].asym.value
    .endif

    ; default processing. if no params/locals are defined, continue

    .if ( !( [rsi].flags & ( PROC_FORCEFRAME or PROC_STACKPARAM or PROC_HAS_VARARG ) ) &&
          ![rsi].locallist && ![rsi].localsize && !sysstack && !resstack && ![rsi].regslist )

        .return( NOT_ERROR )
    .endif

    mov regist,[rsi].regslist

    ; initialize shadow space for register params

    mov rcx,CurrProc
    movzx ecx,[rcx].asym.langtype
    .if ( ModuleInfo.Ofssize == USE64 && ( ecx == LANG_FASTCALL || ecx == LANG_VECTORCALL ) )

        .if ( ModuleInfo.win64_flags & W64F_SAVEREGPARAMS )

            win64_SaveRegParams( rsi )

        .elseif ( Parse_Pass == PASS_1 && ModuleInfo.fctype == FCT_VEC64 )

            ; set param offset to 16

            .for ( ebx = 0, ecx = 16,
                   rdx = [rsi].paralist: rdx: rdx = [rdx].dsym.nextparam, ebx++, ecx += 16 )
                .break .if ( ![rdx].dsym.nextparam )
            .endf
            .for ( rdx = [rsi].paralist: rdx && ebx: rdx = [rdx].dsym.nextparam, ebx--, ecx -= 16 )
                mov [rdx].asym.offs,ecx
            .endf
        .endif
    .endif

    ; Push the USES registers first if -Cs

    .if ( regist && cstack )

        mov offs,0
        push_user_registers( regist, 0, &offs )
        mov regist,NULL
        add argoffs,offs

        .for ( rdi = [rsi].paralist: rdi: rdi = [rdi].dsym.nextparam )
            .break .if ( ![rdi].dsym.nextparam )
        .endf

        .if ( rdi )

            ; v2.23 - skip adding if stackbase is not EBP

            lea rdx,ModuleInfo
            movzx ecx,[rdx].module_info.Ofssize
            mov ecx,[rdx].module_info.basereg[rcx*4]

            .if ( ( [rdi].asym.offs == 8 && ecx == T_EBP ) ||
                  ( [rdi].asym.offs == 16 && ecx == T_RBP ) )

                .for ( rdi = [rsi].paralist: rdi: rdi = [rdi].dsym.nextparam )

                    .if ( [rdi].asym.state != SYM_TMACRO )
                        add [rdi].asym.offs,offs
                    .endif
                .endf
            .endif
        .endif
    .endif

    .if ( sysstack || [rsi].locallist ||
          [rsi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) )

        ; write 80386 prolog code
        ; PUSH [E|R]BP
        ; MOV [E|R]BP, [E|R]SP
        ; SUB [E|R]SP, localsize

        .if ( !( [rsi].flags & PROC_FPO ) && usestack )

            movzx ebx,[rsi].basereg
            movzx ecx,ModuleInfo.Ofssize

            lea rdx,stackreg
            AddLineQueueX(
                "push %r\n"
                "mov %r, %r", ebx, ebx, [rdx+rcx*4] )
        .endif
    .endif

    .if ( resstack || leaf )

        ; in this case, push the USES registers BEFORE the stack space is reserved

        push_user_registers( regist, 0, &offs )
        mov regist,NULL

        mov ebx,[rsi].localsize
        add ebx,resstack

if STACKPROBE

        .if ( Options.chkstack && ebx > 0x1000 )

            AddLineQueueX(
                "mov rax, %d\n"
                "externdef _chkstk:PROC\n"
                "call _chkstk\n"
                "sub rsp, rax", ebx )
        .else
endif

            .if ( ebx )

                movzx ecx,ModuleInfo.Ofssize
                lea   rdx,stackreg
                mov   ecx,[rdx+rcx*4]

                AddLineQueueX( "sub %r, %d", ecx, ebx )
            .endif
if STACKPROBE
        .endif
endif

    .elseif ( [rsi].localsize )

        ; using ADD and the 2-complement has one advantage:
        ; it will generate short instructions up to a size of 128.
        ; with SUB, short instructions work up to 127 only.

        movzx ecx,ModuleInfo.Ofssize
        lea rdx,stackreg
        mov ebx,[rdx+rcx*4]

if STACKPROBE

        .if ( Options.chkstack && [rsi].localsize > 0x1000 )

            AddLineQueueX(
                "externdef _chkstk:PROC\n"
                "mov eax, %d\n"
                "call _chkstk", [rsi].localsize )

            .if ( ModuleInfo.Ofssize == USE64 )
                AddLineQueueX( "sub %r, rax", ebx )
            .endif
        .else
endif
        xor ecx,ecx
        sub ecx,[rsi].localsize

        .if ( Options.masm_compat_gencode || [rsi].localsize == 128 )
            AddLineQueueX( "add %r, %d", ebx, ecx )
        .else
            AddLineQueueX( "sub %r, %d", ebx, [rsi].localsize )
        .endif
if STACKPROBE
        .endif
endif
    .endif

    .if ( [rsi].flags & PROC_LOADDS )

        mov ecx,T_AX
        .if ( ModuleInfo.Ofssize )
            mov ecx,T_EAX
        .endif
        AddLineQueueX(
            "push ds\n"
            "mov ax, %s\n"
            "mov ds, %r", &szDgroup, ecx )
    .endif

    ; Push the USES registers first if stdcall-32
    ; Push the GPR registers of the USES clause

    .if ( regist && cstack == 0 )

        push_user_registers( regist, 0, &offs )
    .endif

runqueue:

    ; v2.33.26 - Use proc language
    mov rdi,CurrProc
    .if ( ModuleInfo.Ofssize == USE64 && [rdi].asym.langtype == LANG_SYSCALL &&
          ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

        .if ( resstack && argstack && resstack )

            .if ( [rsi].regslist && !cstack )

                asmerr( 2008, "User registers inside frame: use -Cs or OPTION CSTACK:ON" )
            .endif

            mov     eax,argstack
            mov     ecx,resstack
            mov     ebx,ecx
            sub     ecx,eax
            sub     ebx,ecx
            add     ebx,[rsi].localsize
            movzx   eax,[rdi].asym.sys_size
            mov     cnt,eax ; chunk size

            .if ( [rsi].basereg == T_RSP )
                mov ebx,ecx     ; [reserved][locals][frame][params]
                add ebx,[rsi].localsize
            .else
                neg ebx         ; [reserved][frame][params][locals]
            .endif

            mov rdi,[rsi].paralist
            .if ( rdi && [rsi].flags & PROC_HAS_VARARG )
                mov rdi,[rdi].dsym.nextparam
            .endif

            .for ( : rdi : rdi = [rdi].dsym.nextparam )

                .if ( [rdi].asym.flags & S_REGPARAM && [rdi].asym.flags & S_USED )

                    mov edx,T_MOV
                    mov al,[rdi].asym.mem_type
                    .if ( al == MT_TYPE )
                        
                        mov rcx,[rdi].asym.type
                        mov al,[rcx].asym.mem_type
                    .endif

                    .if ( al & MT_FLOAT )
                        mov edx,T_MOVAPS
                        .if ( [rdi].asym.sys_size == 4 )
                            mov edx,T_MOVSS
                        .elseif ( [rdi].asym.sys_size == 8 )
                            mov edx,T_MOVSD
                        .endif
                    .endif
                    mov [rdi].asym.state,SYM_STACK
                    mov [rdi].asym.offs,ebx
                    movzx eax,[rsi].basereg
                    movzx ecx,[rdi].dsym.regist
                    AddLineQueueX( "%r [%r][%d],%r", edx, eax, ebx, ecx )
                    add ebx,cnt
                .endif
            .endf
        .endif

        .if ( [rsi].flags & PROC_HAS_VARARG )

            ; v2.33.53

            .if ( [rsi].regslist && !cstack )

                asmerr( 2008, "User registers inside frame: use -Cs or OPTION CSTACK:ON" )
            .endif

            ;
            ; .template valist
            ;    v_argc          dd ?                ; n*8
            ;    v_argf          dd ?                ; 6*8+n*16
            ;    v_end           dq ?                ; &valist+sizeof(valist)
            ;    v_start         dq ?                ; &v_argv
            ;    v_stack         dq ?                ; fs:[0x28]
            ;    v_argv          dq 6 dup(?)         ; rdi..r9
            ;    v_argx          xmmword 8 dup(?)    ; xmm0..7
            ;   .ends
            ;

            mov eax,argstack
            add eax,208
            mov ecx,resstack
            mov ebx,ecx
            sub ecx,eax
            sub ebx,ecx
            add ebx,[rsi].localsize

            .if ( [rsi].basereg == T_RSP )
                mov ebx,ecx     ; [reserved][locals][frame][params]
                add ebx,[rsi].localsize
            .else
                neg ebx         ; [reserved][frame][params][locals]
            .endif
            mov offs,ebx

            mov rdi,[rsi].paralist
            .if ( rdi )
                mov [rdi].dsym.offs,ebx
                mov rdi,[rdi].dsym.nextparam
            .endif

            .for ( ebx = 0, cnt = 0 : rdi : rdi = [rdi].dsym.nextparam )

                .if ( [rdi].asym.mem_type & MT_FLOAT )
                    inc cnt
                .else
                    inc ebx
                .endif
            .endf

            movzx edi,[rsi].basereg
            imul ecx,cnt,16
            AddLineQueueX(
                "mov DWORD PTR [%r][%d],%d\n"
                "mov DWORD PTR [%r+4][%d],48+%d", edi, offs, &[rbx*8], edi, offs, ecx )

            .for ( : ebx < 6: ebx++ )

                lea rcx,elf64_regs
                movzx ecx,byte ptr [rcx+rbx+18]
                lea edx,[rbx*8+0x20]
                AddLineQueueX( "mov [%r+0x%X][%d],%r", edi, edx, offs, ecx )
            .endf
            AddLineQueue( ".if al" )

            mov  ebx,cnt
            imul edi,ebx,16
            add  edi,0x50

            .for ( : ebx < 8 : ebx++, edi += 16 )
                movzx ecx,[rsi].basereg
                AddLineQueueX( "movaps [%r+0x%X][%d],%r", ecx, edi, offs, &[rbx+T_XMM0] )
            .endf

            AddLineQueue( ".endif" )
            movzx edi,[rsi].basereg
            .if ( Options.chkstack )
                AddLineQueueX(
                    "assume fs:nothing\n"
                    "mov rax,fs:[0x28]\n"
                    "assume fs:error\n"
                    "mov [%r+0x18][%d],rax", edi, offs )
            .endif
            mov ecx,argoffs
            .if ( edi == T_RSP )
                add ecx,offs
            .endif
            AddLineQueueX(
                "lea rax,[%r+0x10][%d]\n"
                "mov [%r+0x08][%d],rax\n"
                "lea rax,[%r+0x20][%d]\n"
                "mov [%r+0x10][%d],rax\n"
                "lea rax,[%r][%d]", edi, ecx, edi, offs, edi, offs, edi, offs, edi, offs  )

        .endif
    .endif

    ; special case: generated code runs BEFORE the line.
    ; problem: the size of code above changes in pass 2..

    .if ( ModuleInfo.list && UseSavedState )
        .if ( ( Parse_Pass == PASS_2 && Options.first_pass_listing ) ||
              Parse_Pass == PASS_1 )
            mov [rsi].prolog_list_pos,list_pos
        .else
            mov list_pos,[rsi].prolog_list_pos
        .endif
    .endif

    ; line number debug info also needs special treatment
    ; because current line number is the first true src line
    ; IN the proc.

    mov oldlinenumbers,Options.line_numbers
    mov Options.line_numbers,FALSE ; temporarily disable line numbers

    RunLineQueue()
    mov Options.line_numbers,oldlinenumbers

    .if ( ModuleInfo.list && UseSavedState && ( Parse_Pass > PASS_1 ) )

        mov rcx,LineStoreCurr
        mov ebx,[rcx].line_item.list_pos
        mov [rcx].line_item.list_pos,list_pos

        .if ( ebx > list_pos && !Options.first_pass_listing ) ; remove dublicated code

            mov rcx,[rcx].line_item.next
            .if ( rcx && [rcx].line_item.list_pos > ebx )
                mov ebx,[rcx].line_item.list_pos
            .endif
            sub ebx,list_pos
ifdef __UNIX__  ; keep the last '\n'
            .if ( ebx )
                dec ebx
else
            .if ( ebx >= 2 )
                sub ebx,2
endif
            .endif
            .while ( ebx >= 8 )
                fwrite( "        ", 1, 8, CurrFile[LST*size_t] )
                sub ebx,8
            .endw
            .if ( ebx )
                fwrite( "        ", 1, ebx, CurrFile[LST*size_t] )
            .endif
        .endif
    .endif
    .return( NOT_ERROR )

write_default_prologue endp


;
; v2.12: calculate offsets of local variables; this is now
; done here after ALL locals have been defined.
; will set value of member 'localsize'.
; Notes:
; 64-bit: 16-byte RSP alignment works for
; - FRAME procedures ( if OPTION FRAME:AUTO is set )
; - non-frame procedures if option win64:2 is set
; this means that option win64:4 ( 16-byte stack variable alignment )
; will also work only in those cases!
;

SetLocalOffsets proc __ccall uses rsi rdi rbx info:ptr proc_info

   .new curr:ptr dsym
   .new cntxmm:int_t = 0
   .new cntstd:int_t = 0
   .new start:int_t = 0
   .new regsize:int_t = 0 ; v2.25 - option cstack:on
   .new rspalign:int_t = FALSE
   .new calign:int_t = CurrWordSize
   .new wsize:int_t = CurrWordSize
   .new cstack:int_t = 0

    mov rdi,CurrProc
    movzx ebx,[rdi].asym.langtype

    .if ( ModuleInfo.Ofssize == USE64 || ( ModuleInfo.Ofssize == USE32 &&
            ( ebx == LANG_STDCALL || ebx == LANG_C || ebx == LANG_SYSCALL ) ) )
        .if ( ModuleInfo.xflag & OPT_CSTACK )
            inc cstack
        .endif
    .endif

    .if ( ModuleInfo.fctype == FCT_VEC64 )
        mov wsize,16
    .endif

    mov rsi,info
    .if ( [rsi].flags & PROC_ISFRAME ||
         ( ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) &&
            ( ModuleInfo.fctype == FCT_WIN64 ||
              ModuleInfo.fctype == FCT_VEC64 ||
              ModuleInfo.fctype == FCT_ELF64 ) ) )
        mov rspalign,TRUE
        .if ( ModuleInfo.win64_flags & W64F_STACKALIGN16 || ModuleInfo.fctype == FCT_VEC64 )
            mov calign,16
        .endif
    .endif

    ; in 64-bit, if the FRAME attribute is set, the space for the registers
    ; saved by the USES clause is located ABOVE the local variables!
    ; v2.09: if stack space is to be reserved for INVOKE ( option WIN64:2 ),
    ; the registers are also saved ABOVE the local variables.

    .if ( [rsi].flags & PROC_FPO || rspalign )

        ; count registers to be saved ABOVE local variables.
        ; v2.06: the list may contain xmm registers, which have size 16!

        .if ( [rsi].regslist )

            mov rdi,[rsi].regslist
            movzx ebx,word ptr [rdi]
            .for ( rdi += 2 : ebx : ebx--, rdi += 2 )
                movzx edx,word ptr [rdi]
                .if ( GetValueSp( edx ) & OP_XMM )
                    inc cntxmm
                .else
                    inc cntstd
                .endif
            .endf
        .endif

        ; in case there's no frame register, adjust start offset.

        .if ( [rsi].flags & PROC_FPO ||
              ( [rdi].asym.langtype == LANG_WATCALL &&
                [rsi].parasize <= 8*4 &&
                [rsi].locallist == NULL ) ||
              ( [rsi].parasize == 0 && [rsi].locallist == NULL ) )
            mov start,CurrWordSize
        .endif

        .if ( rspalign )

            mov eax,cntstd
            mul wsize
            add eax,start
            mov [rsi].localsize,eax

            .if ( cntxmm )

                imul eax,cntxmm,16
                add eax,[rsi].localsize
                mov [rsi].localsize,ROUND_UP( eax, 16 )
            .endif
        .endif
    .endif

    .if ( cntxmm )

        mov rcx,CurrProc
        or  [rcx].asym.sflags,S_LOCALGPR
    .endif

    ; size of user resisters should be added if SP used as base
    ; or BP used and registers pushed before BP (option cstack)

    lea   rdx,ModuleInfo
    movzx ecx,[rdx].module_info.Ofssize
    mov   ebx,[rdx].module_info.basereg[rcx*4]
    imul  ecx,cntxmm,16
    mov   eax,wsize
    mul   cntstd
    add   eax,ecx

    .if ( eax && cstack )

        .if ( calign == 16 && ebx == T_RSP )
            ROUND_UP( eax, 16 )
        .endif
        .if ( ebx == T_EBP || ebx == T_RBP )
            mov regsize,eax
        .elseif ( ebx == T_ESP )
            neg eax
            mov regsize,eax
        .endif
    .endif

    ; scan the locals list and set member sym.offset

    .for ( rdi = [rsi].locallist: rdi: rdi = [rdi].dsym.nextlocal )

        xor eax,eax
        .if ( [rdi].asym.total_size )
            mov eax,[rdi].asym.total_size
            cdq
            div [rdi].asym.total_length
        .endif
        mov ecx,eax
        add [rsi].localsize,[rdi].asym.total_size
        .if ( ecx > calign )
            mov [rsi].localsize,ROUND_UP( [rsi].localsize, calign )
        .elseif ( ecx ) ; v2.04: skip if size == 0
            mov [rsi].localsize,ROUND_UP( [rsi].localsize, ecx )
        .endif
        mov eax,[rsi].localsize
        neg eax
        add eax,regsize
        mov [rdi].asym.offs,eax
    .endf

    ; v2.11: localsize must be rounded before offset adjustment if fpo

    mov [rsi].localsize,ROUND_UP( [rsi].localsize, wsize )

    ; RSP 16-byte alignment?

    .if ( rspalign )
        mov [rsi].localsize,ROUND_UP( [rsi].localsize, 16 )
    .endif

    ; v2.11: recalculate offsets for params and locals if there's no frame pointer.
    ; Problem in 64-bit: option win64:2 triggers the "stack space reservation" feature -
    ; but the final value of this space is known at the procedure's END only.
    ; Hence in this case the values calculated below are "preliminary".

    .if ( [rsi].flags & PROC_FPO )

        movzx edi,CurrWordSize

        .if ( rspalign )

            mov ecx,[rsi].localsize
            mov ebx,ecx
            sub ebx,edi
            sub ebx,start

        .else

            mov eax,cntstd
            mul edi
            mov ecx,[rsi].localsize
            add ecx,eax
            mov ebx,ecx
            sub ebx,edi
        .endif

        ; subtract CurrWordSize value for params, since no space is required
        ; to save the frame pointer value

        .for ( rdi = [rsi].locallist: rdi: rdi = [rdi].dsym.nextlocal )
            add [rdi].asym.offs,ecx
        .endf
        .for ( rdi = [rsi].paralist: rdi: rdi = [rdi].dsym.nextparam )
            ; added v2.33.25
            .if ( [rdi].asym.state != SYM_TMACRO )
                add [rdi].asym.offs,ebx
            .endif
        .endf
    .endif

    ; v2.12: if the space used for register saves has been added to localsize,
    ; the part that covers "pushed" GPRs has to be subtracted now, before
    ; prologue code is generated.

    .if ( rspalign )

        mov eax,cntstd
        mul wsize
        add eax,start
        sub [rsi].localsize,eax
    .endif
    ret

SetLocalOffsets endp


write_prologue proc __ccall uses rsi rdi tokenarray:ptr asm_tok

    mov rdi,CurrProc
    mov rsi,[rdi].dsym.procinfo

    .if ( Parse_Pass == PASS_1 )
        and [rdi].asym.sflags,not ( S_STKUSED or S_ARGUSED or S_LOCALGPR )
    .endif

    ; reset @ProcStatus flag

    and ProcStatus,not PRST_PROLOGUE_NOT_DONE

    .if ( ModuleInfo.endbr && ModuleInfo.prologuemode != PEM_NONE &&
          ModuleInfo.langtype == LANG_SYSCALL )
        .if ( ModuleInfo.Ofssize == USE64 )
            AddLineQueue( "endbr64" )
        .elseif ( ModuleInfo.Ofssize == USE32 )
            AddLineQueue( "endbr32" )
        .endif
    .endif

    .if ( ( ModuleInfo.fctype == FCT_WIN64 ||
            ModuleInfo.fctype == FCT_VEC64 ||
            ModuleInfo.fctype == FCT_ELF64 ) &&
          ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        ; in pass one init reserved stack with 4*8 to force stack frame creation

        mov rcx,sym_ReservedStack
        movzx edx,[rdi].asym.langtype
        .if ( Parse_Pass == PASS_1 )
            mov [rcx].asym.value,4 * sizeof( uint_64 )
            .if ( dl == LANG_VECTORCALL )
                mov [rcx].asym.value,6 * 16
            .elseif ( dl == LANG_SYSCALL )
                mov [rcx].asym.value,0
                .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
                    .for ( ecx = 0, rdx = [rsi].paralist : rdx : rdx = [rdx].dsym.nextparam )
                        .if ( [rdx].asym.flags & S_REGPARAM )
                            add ecx,8
                        .endif
                    .endf
                    .for ( rdx = [rsi].paralist : rdx : rdx = [rdx].dsym.nextparam )
                        .if !( [rdx].asym.flags & S_REGPARAM )
                            sub [rdx].asym.offs,ecx
                        .endif
                    .endf
                .endif
            .endif
        .else
            mov [rcx].asym.value,[rsi].ReservedStack
        .endif
    .endif

    .if ( Parse_Pass == PASS_1 )

        ; v2.12: calculation of offsets of local variables is done delayed now

        SetLocalOffsets( rsi )
    .endif
    or ProcStatus,PRST_INSIDE_PROLOGUE

    ; there are 3 cases:
    ; option prologue:NONE          proc_prologue == NULL
    ; option prologue:default       *proc_prologue == NULLC
    ; option prologue:usermacro     *proc_prologue != NULLC

    .if ( ModuleInfo.prologuemode == PEM_DEFAULT )
        write_default_prologue()
    .elseif ( ModuleInfo.prologuemode == PEM_NONE )
    .else
        write_userdef_prologue( tokenarray )
    .endif
    and ProcStatus,not PRST_INSIDE_PROLOGUE

    ; v2.10: for debug info, calculate prologue size

    mov ecx,GetCurrOffset()
    sub ecx,[rdi].asym.offs
    mov [rsi].size_prolog,cl
    ret

write_prologue endp


pop_register proc __ccall private uses rsi rdi regist:ptr word

    ; Pop the register when a procedure ends

    ldr rsi,regist
    .return .if ( rsi == NULL )

    movzx edi,word ptr [rsi]
    lea rsi,[rsi+rdi*2]
    .for ( : edi: edi--, rsi -= 2 )

        ; don't "pop" xmm registers

        movzx ecx,word ptr [rsi]
        .continue .if ( GetValueSp( ecx ) & OP_XMM )
        AddLineQueueX( "pop %r", ecx )
    .endf
    ret

pop_register endp

;
; write default epilogue code
; if a RET/IRET instruction has been found inside a PROC.
;
; epilog code timings
;
;                                                 best result
;             size  86  286  386  486  P      86  286  386  486  P
; mov sp,bp   2     2   2    2    1    1
; pop bp      2     8   5    4    4    1
;            -----------------------------
;             4     10  7    6    5    2      x             x    x
;
; mov esp,ebp 2     -   -    2    1    1
; pop ebp     2     -   -    4    4    1
;            -----------------------------
;             4     -   -    6    5    2                    x    x
;
; leave       1     -   5    4    5    3          x    x    x
;
; !!!! DECISION !!!!
;
; leave will be used for .286 and .386
; .286 code will be best working on 286,386 and 486 processors
; .386 code will be best working on 386 and 486 processors
; .486 code will be best working on 486 and above processors
;
;   without LEAVE
;
;        86  286  386  486  P
;  .8086  0   -2   -2  0    +1
;  .286   -   -2   -2  0    +1
;  .386   -   -    -2  0    +1
;  .486   -   -    -   0    +1
;
;   LEAVE 286 only
;
;        86  286  386  486  P
;  .8086  0   -2   -2  0    +1
;  .286   -   0    +2  0    -1
;  .386   -   -    -2  0    +1
;  .486   -   -    -   0    +1
;
;   LEAVE 286 and 386
;
;        86  286  386  486  P
;  .8086  0   -2   -2  0    +1
;  .286   -   0    +2  0    -1
;  .386   -   -    0   0    -1
;  .486   -   -    -   0    +1
;
;   LEAVE 286, 386 and 486
;
;        86  286  386  486  P
;  .8086  0   -2   -2  0    +1
;  .286   -   0    +2  0    -1
;  .386   -   -    0   0    -1
;  .486   -   -    -   0    -1

write_default_epilogue proc __ccall private uses rsi rdi rbx

   .new info:ptr proc_info
   .new sysstack:int_t
   .new leav:int_t = 0
   .new resstack:int_t = 0
   .new cstack:int_t
   .new sreg:int_t
   .new usestack:int_t = 1

    mov rdi,CurrProc
    mov rsi,[rdi].dsym.procinfo
    mov info,rsi
    mov cl,[rdi].asym.langtype
    mov cstack,use_cstack()
    mov sysstack,use_sysstack()


    .if ( ModuleInfo.Ofssize == USE64 && ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) &&
          ( cl == LANG_WATCALL || cl == LANG_FASTCALL || cl == LANG_VECTORCALL ) )

        ;
        ; Reserved stack is used if a 64-bit fastcall or vectocall is invoked
        ; - see fastcall.asm: ms64_fcstart(), hll.asm: LKRenderHllProc()
        ;
        .if ( [rsi].flags & PROC_HAS_VARARG )
            or [rdi].asym.sflags,S_ARGUSED
        .else
            .for ( rdx = [rsi].paralist : rdx : rdx = [rdx].dsym.nextparam )
                .if ( [rdx].asym.flags & S_USED )
                    or [rdi].asym.sflags,S_ARGUSED
                .endif
            .endf
        .endif

        .if ( !( [rdi].asym.sflags & S_STKUSED ) && ![rsi].locallist )

            mov rdx,sym_ReservedStack
            .if ( rdx )
                mov [rdx].asym.value,0 ; leaf: no reserved stack needed..
            .endif

            .if ( !( [rdi].asym.sflags & S_LOCALGPR ) && [rsi].localsize == 8 )

                mov [rsi].localsize,0 ; no alignment needed..

                .if ( ModuleInfo.basereg[USE64*4] == T_RSP ) ; adjust stack params ?

                    .for ( rdx = [rsi].paralist: rdx: rdx = [rdx].dsym.nextparam )
                        .if ( [rdx].asym.state != SYM_TMACRO )
                            sub [rdx].asym.offs,8
                        .endif
                    .endf
                .endif
            .endif
            .if ( !( [rdi].asym.sflags & ( S_ARGUSED or S_LOCALGPR ) ) &&
                  [rsi].localsize == 0 && [rsi].regslist == NULL )
                mov usestack,0
            .endif
        .endif
    .endif

    .if ( [rsi].locallist || sysstack ||
          [rsi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) )
        inc leav
    .endif

    movzx ecx,ModuleInfo.Ofssize
    lea rdx,stackreg
    mov sreg,[rdx+rcx*4]

    .if ( [rsi].flags & PROC_ISFRAME )


        .if ( ModuleInfo.frame_auto & 1 )

            ; Win64 default epilogue if PROC FRAME and OPTION FRAME:AUTO is set

            ; restore non-volatile xmm registers

            .if ( [rsi].regslist )

                ; v2.12: space for xmm saves is now included in localsize
                ; so first thing to do is to count the xmm regs that were saved

                mov rdi,[rsi].regslist
                movzx ebx,word ptr [rdi]

                .for ( rdi += 2, ecx = 0: ebx: ebx--, rdi += 2 )
                    movzx eax,word ptr [rdi]
                    .if ( GetValueSp( eax ) & OP_XMM )
                        inc ecx
                    .endif
                .endf

                .if ( ecx )

                    imul ecx,ecx,16
                    mov ebx,[rsi].localsize
                    sub ebx,ecx
                    and ebx,not (16-1)

                    mov rdi,[rsi].regslist
                    movzx esi,word ptr [rdi]

                    .for ( rdi += 2 : esi: esi--, rdi += 2 )

                        movzx ecx,word ptr [rdi]

                        .if ( GetValueSp( ecx ) & OP_XMM )

                            ; v2.11: use @ReservedStack only if option win64:2 is set

                            .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
                                mov rdx,sym_ReservedStack
                                AddLineQueueX( "movdqa %r, [%r + %u + %s]", ecx, sreg, ebx, [rdx].asym.name )
                            .else
                                AddLineQueueX( "movdqa %r, [%r + %u]", ecx, sreg, ebx )
                            .endif
                            add ebx,16
                        .endif
                    .endf
                .endif
            .endif

            mov rsi,info

            .if ( ( leav && [rsi].flags & PROC_PE_TYPE ) &&
                  ( cstack || ( ( sysstack || ![rsi].regslist ) && [rsi].basereg == T_RBP ) ) )

                .if ( cstack == 0 )
                    pop_register( [rsi].regslist )
                .endif

                .if ( ( !sysstack && [rsi].locallist == NULL ) &&
                      !( [rsi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) ) &&
                      resstack == 0 )

                    .if ( cstack )
                        pop_register( [rsi].regslist )
                    .endif
                    .return
                .endif
                .if ( usestack )
                    AddLineQueue( "leave" )
                .endif
                .if ( cstack )
                    pop_register( [rsi].regslist )
                .endif

            .else

                mov ebx,sreg
                .if ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
                      ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

                    mov rdx,sym_ReservedStack
                    mov edx,[rdx].asym.value
                    add edx,[rsi].localsize
                    .ifnz
                        AddLineQueueX( "add %r, %d", ebx, edx )
                    .endif

                .elseif ( [rsi].localsize )
                    AddLineQueueX( "add %r, %d", ebx, [rsi].localsize )
                .endif

                .if ( cstack == 0 )
                    pop_register( [rsi].regslist )
                .endif

                movzx ecx,[rsi].basereg
                .if ( ( GetRegNo( ecx ) != 4 && ( [rsi].parasize != 0 || [rsi].locallist != NULL ) ) )
                    AddLineQueueX( "pop %r", ecx )
                .endif

                .if ( cstack )
                    pop_register( [rsi].regslist )
                .endif
            .endif
        .endif
        .return
    .endif

    .if ( ModuleInfo.Ofssize == USE64 &&
         ( ModuleInfo.fctype == FCT_WIN64 ||
           ModuleInfo.fctype == FCT_VEC64 ||
           ModuleInfo.fctype == FCT_ELF64 ) &&
         ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        mov rcx,sym_ReservedStack
        mov resstack,[rcx].asym.value

        ; if no framepointer was pushed, add 8 to align stack on OWORD
        ; v2.12: obsolete; localsize contains correct value.

        .if ( cstack && leav && [rsi].flags & PROC_PE_TYPE )

            ; v2.21: leave will follow..

        .elseif ( !cstack && leav && [rsi].flags & PROC_PE_TYPE &&
                  ( sysstack || ![rsi].regslist ) && [rsi].basereg == T_RBP )

            ; v2.27: leave will follow..

        .elseif ( resstack || [rsi].localsize )
            mov ebx,sreg
            mov rdx,sym_ReservedStack
            AddLineQueueX( "add %r, %d + %s", ebx, [rsi].localsize, [rdx].asym.name )
        .endif
    .endif

    .if ( cstack == 0 )

        ; Pop the registers

        pop_register( [rsi].regslist )

        .if ( [rsi].flags & PROC_LOADDS )
            AddLineQueue( "pop ds" )
        .endif
    .endif

    .if ( ( !sysstack && [rsi].locallist == NULL ) &&
          !( [rsi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) ) &&
          resstack == 0 )

        .if ( cstack )

            ; Pop the registers

            pop_register( [rsi].regslist )
            .if ( [rsi].flags & PROC_LOADDS )
                AddLineQueue( "pop ds" )
            .endif
        .endif
        .return
    .endif

    ; restore registers e/sp and e/bp.
    ; emit either "leave" or "mov e/sp,e/bp, pop e/bp".

    .if ( !leav )

    .elseif ( [rsi].flags & PROC_PE_TYPE )

        .if ( usestack )
            AddLineQueue( "leave" )
        .endif
    .else

        .if ( [rsi].flags & PROC_FPO )
            .if ( ModuleInfo.Ofssize == USE64 &&
                  ( ModuleInfo.fctype == FCT_WIN64 ||
                    ModuleInfo.fctype == FCT_VEC64 ||
                    ModuleInfo.fctype == FCT_ELF64 ) &&
                  ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

            .elseif ( [rsi].localsize )

                AddLineQueueX( "add %r, %d", sreg, [rsi].localsize )
            .endif

        .elseif ( usestack )

            ; MOV [E|R]SP, [E|R]BP
            ; POP [E|R]BP

            .if ( [rsi].localsize != 0 )
                AddLineQueueX( "mov %r, %r", sreg, [rsi].basereg )
            .endif
            AddLineQueueX( "pop %r", [rsi].basereg )
        .endif
    .endif

    .if ( cstack )

        ; Pop the registers

        pop_register( [rsi].regslist )

        .if ( [rsi].flags & PROC_LOADDS )
            AddLineQueue( "pop ds" )
        .endif
    .endif
    ret

write_default_epilogue endp

;
; write userdefined epilogue code
; if a RET/IRET instruction has been found inside a PROC.
;

write_userdef_epilogue proc __ccall private uses rsi rdi rbx flag_iret:int_t, tokenarray:ptr asm_tok

    mov rdi,CurrProc
    mov rsi,[rdi].dsym.procinfo
    movzx ebx,[rdi].asym.langtype

   .new regs:ptr word
   .new i:int_t
   .new p:string_t
   .new is_exitm:int_t
   .new info:ptr proc_info = rsi
   .new flags:int_t
   .new dir:ptr dsym
   .new reglst[128]:char_t
   .new buffer[MAX_LINE_LEN]:char_t ; stores string for RunMacro()

    mov dir,SymSearch( ModuleInfo.proc_epilogue )
    .if ( eax == NULL || [rax].asym.state != SYM_MACRO || [rax].asym.mac_flag & M_ISFUNC )
        .return( asmerr( 2121, ModuleInfo.proc_epilogue ) )
    .endif

    ; to be compatible with ML64, translate FASTCALL to 0 (not 7)

    mov edx,ebx
    .if ( ebx == LANG_FASTCALL && ModuleInfo.fctype == FCT_WIN64 )
        mov edx,0
    .endif
    .if ( ebx == LANG_C || ebx == LANG_SYSCALL || ebx == LANG_FASTCALL )
        or edx,0x10
    .endif

    .if ( [rdi].asym.mem_type == MT_FAR )
        or edx,0x20
    .endif
    .if ( !( [rdi].asym.flags & S_ISPUBLIC ) )
        or edx,0x40
    .endif

    ; v2.11: set bit 7, the export flag

    .if ( [rsi].flags & PROC_ISEXPORT )
        or edx,0x80
    .endif
    .if ( flag_iret )
        or edx,0x100 ; bit 8: 1 if IRET
    .endif
    mov flags,edx

    mov rdi,[rsi].regslist
    lea rsi,reglst
    .if ( rdi )
        movzx ebx,word ptr [rdi]
        lea rdi,[rdi+rbx*2]
        .for ( : ebx: rdi -= 2, ebx-- )
            movzx ecx,word ptr [rdi]
            GetResWName( ecx, rsi )
            add rsi,tstrlen( rsi )
            .if ( ebx != 1 )
                mov byte ptr [rsi],','
                inc rsi
            .endif
        .endf
    .endif
    mov byte ptr [rsi],NULLC

    mov rsi,info
    mov rdi,CurrProc
    lea rcx,@CStr("")
    .if ( [rsi].prologuearg )
        mov rcx,[rsi].prologuearg
    .endif
    tsprintf( &buffer,"%s, 0%XH, 0%XH, 0%XH, <<%s>>, <%s>",
            [rdi].asym.name, flags, [rsi].parasize, [rsi].localsize, &reglst, rcx )

    mov ecx,Token_Count
    inc ecx
    mov i,ecx
    Tokenize( &buffer, i, tokenarray, TOK_RESCAN )

    ; if -EP is on, emit "epilogue: none"

    .if ( Options.preprocessor_stdout )
        tprintf( "option epilogue:none\n" )
    .endif

    RunMacro( dir, i, tokenarray, NULL, 0, &is_exitm )
    mov eax,i
    dec eax
    mov Token_Count,eax
   .return( NOT_ERROR )

write_userdef_epilogue endp


;
; a RET <nnnn> or IRET/IRETD has occured inside a PROC.
; count = number of tokens in buffer (=Token_Count)
; it's ensured already that ModuleInfo.proc_epilogue isn't NULL.
;

RetInstr proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok, count:int_t

   .new info:ptr proc_info
   .new is_iret:int_t = FALSE
   .new p:string_t
   .new buffer[MAX_LINE_LEN]:char_t ; stores modified RETN/RETF/IRET instruction

    ldr ecx,i
    ldr rdx,tokenarray

    imul ebx,ecx,asm_tok
    add rbx,rdx
    .if ( [rbx].tokval == T_IRET || [rbx].tokval == T_IRETD || [rbx].tokval == T_IRETQ )
        mov is_iret,TRUE
    .elseif ( [rbx].tokval == T_RET && ModuleInfo.RetStack )
        mov rcx,ModuleInfo.RetStack
        mov ecx,[rcx].hll_item.labels[LEXIT*4]
        AddLineQueueX( "%s%s", GetLabelStr( ecx, &buffer ), LABELQUAL )
        mov ModuleInfo.RetStack,NULL
    .endif

    .if ( ModuleInfo.epiloguemode == PEM_MACRO )
        ;
        ; don't run userdefined epilogue macro if pass > 1
        ;
        .if ( UseSavedState )
            .if ( Parse_Pass > PASS_1 )
                .return( ParseLine( tokenarray ) )
            .endif
            ;
            ; handle the current line as if it is REPLACED by the macro content
            ;
            mov rcx,LineStoreCurr
            mov [rcx].line_item.line,';'
        .endif
        .return( write_userdef_epilogue( is_iret, tokenarray ) )
    .endif

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL )
    .endif

    mov rdi,tstrcpy( &buffer, [rbx].string_ptr )
    add rdi,tstrlen( rax )

    write_default_epilogue()

    mov rcx,CurrProc
    mov rsi,[rcx].dsym.procinfo

    ;
    ; skip this part for IRET
    ;
    .if ( is_iret == FALSE )
        .if ( [rcx].asym.mem_type == MT_FAR )
            mov al,'f' ; ret -> retf
        .else
            mov al,'n' ; ret -> retn
        .endif
        stosb
    .endif

    inc i ; skip directive
    add rbx,asm_tok
    mov edx,count

    .if ( [rsi].parasize || ( edx != i ) )
        mov al,' '
        stosb
    .endif
    mov byte ptr [rdi],NULLC

    ;
    ; RET without argument? Then calculate the value
    ;
    .if ( is_iret == FALSE && edx == i )
        .if ( ModuleInfo.epiloguemode != PEM_NONE )
            movzx eax,[rcx].asym.langtype
            .switch( eax )
            .case LANG_BASIC
            .case LANG_FORTRAN
            .case LANG_PASCAL
                .if ( [rsi].parasize != 0 )
                    xor eax,eax
                    .if ( ModuleInfo.radix != 10 )
                        mov al,'t'
                    .endif
                    tsprintf( rdi, "%d%c", [rsi].parasize, eax )
                .endif
                .endc
            .case LANG_SYSCALL
                .endc .if ( ModuleInfo.Ofssize != USE64 )
            .case LANG_FASTCALL
            .case LANG_VECTORCALL
                GetFastcallId( eax )
                dec eax
                imul ecx,eax,fastcall_conv
ifdef _WIN64
                lea rax,fastcall_tab
                add rax,rcx
                [rax].fastcall_conv.handlereturn( CurrProc, &buffer )
else
                fastcall_tab[ecx].handlereturn( CurrProc, &buffer )
endif
                .endc
            .case LANG_STDCALL
                .if ( !( [rsi].flags & PROC_HAS_VARARG ) && [rsi].parasize )
                    xor eax,eax
                    .if ( ModuleInfo.radix != 10 )
                        mov al,'t'
                    .endif
                    tsprintf( rdi, "%d%c", [rsi].parasize, eax )
                .endif
                .endc
            .endsw
        .endif
    .else
        ;
        ; v2.04: changed. Now works for both RET nn and IRETx
        ; v2.06: changed. Now works even if RET has ben "renamed"
        ;
        tstrcpy( rdi, [rbx].tokpos )
    .endif
    AddLineQueue( &buffer )
    RunLineQueue()
   .return( NOT_ERROR )

RetInstr endp

;
; init this module. called for every pass.
;

ProcInit proc __ccall

    mov ProcStack,NULL
    mov CurrProc ,NULL
    mov strFUNC,0
    mov procidx,1
    mov ProcStatus,0
    ;
    ; v2.09: reset prolog and epilog mode
    ;
    mov ModuleInfo.prologuemode,PEM_DEFAULT
    mov ModuleInfo.epiloguemode,PEM_DEFAULT
    ;
    ; v2.06: no forward references in INVOKE if -Zne is set
    ;
    xor eax,eax
    .if ( ModuleInfo.strict_masm_compat )
        mov al,EXPF_NOUNDEF
    .endif
    mov ModuleInfo.invoke_exprparm,al
    mov ModuleInfo.basereg[USE16*4],T_BP
    mov ModuleInfo.basereg[USE32*4],T_EBP
    mov ModuleInfo.basereg[USE64*4],T_RBP
    mov unw_segs_defined,0
    ret

ProcInit endp

    end
