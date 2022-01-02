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

public  ProcStatus
public  procidx
public  StackAdj

define  T <@CStr>

.data

ms64_regs           special_token T_RCX, T_RDX, T_R8, T_R9

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
unw_info            UNWIND_INFO <>
;
; v2.11: changed 128 -> 258; actually, 255 is the max # of unwind codes
;
unw_code            UNWIND_CODE 258 dup(<>)

;
; @ReservedStack symbol; used when option W64F_AUTOSTACKSP has been set
;
sym_ReservedStack   ptr asym 0 ;; max stack space required by INVOKE

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

fmtstk0 string_t \
    T("sub %r, %d"),
    T("%r %d"),
    T("mov %r, %d")

fmtstk1 string_t \
    T("sub %r, %d + %s"),
    T("%r %d + %s"),
    T("mov %r, %d + %s")

    .code

    assume  ebx:ptr asm_tok

ifdef FCT_ELF64
externdef elf64_regs:byte
endif

pushitem proc private stk:ptr, elmt:ptr

    LclAlloc( sizeof( qnode ) )
    mov edx,stk
    mov ecx,[edx]
    mov [eax].qnode.next,ecx
    mov ecx,elmt
    mov [eax].qnode.elmt,ecx
    mov [edx],eax
    ret

pushitem endp

popitem proc private stk:ptr

    mov edx,stk
    mov ecx,[edx]
    mov [edx],[ecx].qnode.next
    mov eax,[ecx].qnode.elmt
    ret

popitem endp

push_proc proc private p:ptr dsym
    .if ( Parse_Pass == PASS_1 ) ;; get the locals stored so far
        SymGetLocal( p )
    .endif
    pushitem( &ProcStack, p )
    ret
push_proc endp

pop_proc proc private
    .return( NULL ) .if ( ProcStack == NULL )
    .return( popitem( &ProcStack ) )
pop_proc endp

;
; LOCAL directive. Syntax:
; LOCAL symbol[,symbol]...
; symbol:name [[count]] [:[type]]
; count: number of array elements, default is 1
; type:  qualified type [simple type, structured type, ptr to simple/structured type]
;

LocalDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local name  : string_t
  local loc   : ptr dsym
  local ti    : qualified_type

    .if ( Parse_Pass != PASS_1 ) ;; everything is done in pass 1
        .return( NOT_ERROR )
    .endif

    .if ( !( ProcStatus & PRST_PROLOGUE_NOT_DONE ) || CurrProc == NULL )
        .return( asmerr( 2012 ) )
    .endif

    mov esi,CurrProc
    mov esi,[esi].dsym.procinfo
    assume esi:ptr proc_info

    ; ensure the fpo bit is set - it's too late to set it in write_prologue().
    ; Note that the fpo bit is set only IF there are locals or arguments.
    ; fixme: what if pass > 1?

    movzx eax,[esi].basereg
    .if ( GetRegNo( eax ) == 4 )
        or [esi].flags,PROC_FPO
        or ProcStatus,PRST_FPO
    .endif

    inc i ; go past LOCAL
    mov ebx,tokenarray.tokptr(i)

    .repeat

        .if ( [ebx].token != T_ID )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        mov name,[ebx].string_ptr

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

        mov [eax].asym.state,SYM_STACK
        or  [eax].asym.flags,S_ISDEFINED
        mov [eax].asym.total_length,1 ;; v2.04: added
        .switch ( ti.Ofssize )
        .case USE16
            mov [eax].asym.mem_type,MT_WORD
            mov ti.size,sizeof( uint_16 )
            .endc
        .default
            mov [eax].asym.mem_type,MT_DWORD
            mov ti.size,sizeof( uint_32 )
            .endc
        .endsw

        inc i ; go past name
        add ebx,16

        ; get the optional index factor: local name[xx]:...

        .if ( [ebx].token == T_OP_SQ_BRACKET )

           .new opndx:expr

            inc i ; go past '['
            add ebx,16

            ; scan for comma or colon. this isn't really necessary,
            ; but will prevent the expression evaluator from emitting
            ; confusing error messages.

            .for ( ecx = i, edx = ebx: ecx < Token_Count: ecx++, edx += 16 )
                .break .if ( [edx].asm_tok.token == T_COMMA || [edx].asm_tok.token == T_COLON )
            .endf
            .return .if ( EvalOperand( &i, tokenarray, ecx, &opndx, 0 ) == ERROR )

            .if ( opndx.kind != EXPR_CONST )
                asmerr( 2026 )
                mov opndx.value,1
            .endif

            ; zero is allowed as value!

            mov ebx,tokenarray.tokptr(i)
            mov ecx,loc
            mov [ecx].asym.total_length,opndx.value
            or  [ecx].asym.flag1,S_ISARRAY
            .if ( [ebx].token == T_CL_SQ_BRACKET )
                inc i ; go past ']'
                add ebx,16
            .else
                asmerr( 2045 )
            .endif
        .endif


        ; get the optional type: local name[xx]:type

        .if ( [ebx].token == T_COLON )

            inc i
            .return .if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )

            mov ebx,tokenarray.tokptr(i)
            mov ecx,loc
            mov [ecx].asym.mem_type,ti.mem_type
            .if ( ti.mem_type == MT_TYPE )
                mov [ecx].asym.type,ti.symtype
            .else
                mov [ecx].asym.target_type,ti.symtype
            .endif
        .endif
        mov ecx,loc
        mov [ecx].asym.is_ptr,ti.is_ptr
        mov [ecx].asym.is_far,ti.is_far
        mov [ecx].asym.Ofssize,ti.Ofssize
        mov [ecx].asym.ptr_memtype,ti.ptr_memtype
        mov eax,ti.size
        mul [ecx].asym.total_length
        mov [ecx].asym.total_size,eax

        ; v2.12: address calculation is now done in SetLocalOffsets()

        .if ( [esi].locallist == NULL )
            mov [esi].locallist,ecx
        .else
            .for( edx = [esi].locallist: [edx].dsym.nextlocal : edx = [edx].dsym.nextlocal )
            .endf
            mov [edx].dsym.nextlocal,ecx
        .endif

        .if ( [ebx].token != T_FINAL )
            .if ( [ebx].token == T_COMMA )
                mov eax,i
                inc eax
                .if ( eax < Token_Count )
                    inc i
                    add ebx,16
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

UpdateStackBase proc sym:ptr asym, opnd:ptr expr

    mov edx,opnd
    .if ( edx )
        mov StackAdj,[edx].expr.uvalue
        mov StackAdjHigh,[edx].expr.hvalue
    .endif
    mov ecx,sym
    mov [ecx].asym.value,StackAdj
    mov [ecx].asym.value3264,StackAdjHigh
    ret

UpdateStackBase endp

;
; read value of @ProcStatus variable
;

UpdateProcStatus proc sym:ptr asym, opnd:ptr expr

    xor eax,eax
    .if ( CurrProc )
        mov eax,ProcStatus
    .endif
    mov ecx,sym
    mov [ecx].asym.value,eax
    ret
UpdateProcStatus endp

;
; Added v2.27
;

GetFastcallId proc langtype:int_t

    mov ecx,langtype
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

MacroInline proto :string_t, :int_t, :string_t, :string_t, :int_t

ParseInline proc private uses esi ebx sym:ptr asym, curr:ptr asm_tok, tokenarray:ptr asm_tok

    .if ( Parse_Pass == PASS_1 )

        mov ecx,sym
        or [ecx].asym.flag2,S_ISINLINE

        xor esi,esi
        xor eax,eax
        mov ebx,curr
        mov ecx,tokenarray
        add ecx,32

        .if ( [ecx].asm_tok.token == T_RES_ID &&
              [ecx].asm_tok.tokval >= T_CCALL &&
              [ecx].asm_tok.tokval <= T_WATCALL )
            add ecx,16
        .endif

        .for ( edx = ecx: edx < ebx: edx += 16 )
            .if ( [edx].asm_tok.token == T_COLON )
                inc esi
            .elseif ( edx > ecx && [edx].asm_tok.token == T_COMMA )
                inc eax
            .endif
        .endf

        .if ( eax > esi )
            inc eax
            mov esi,eax
        .endif

        mov [ebx].token,T_FINAL
        mov eax,[ebx].tokpos
        mov byte ptr [eax],0

        .if ( [edx-16].asm_tok.token == T_RES_ID && [edx-16].asm_tok.tokval == T_VARARG )
            mov edx,1
        .else
            xor edx,edx
        .endif

        mov eax,tokenarray
        MacroInline([eax].asm_tok.string_ptr, esi, [ecx].asm_tok.tokpos, [ebx].string_ptr, edx )
    .endif
    ret

ParseInline endp

ParseParams proc private uses esi edi ebx p:ptr dsym, i:int_t, tokenarray:ptr asm_tok, IsPROC:int_t

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

    mov ecx,p
    mov esi,[ecx].dsym.procinfo
    movzx edi,[ecx].asym.langtype
   .new fastcall_id:int_t = GetFastcallId( edi )

    ; find "first" parameter ( that is, the first to be pushed in INVOKE )

    .if ( edi == LANG_STDCALL || edi == LANG_C || \
          edi == LANG_SYSCALL || edi == LANG_VECTORCALL || \
          ( edi == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) || \
          edi == LANG_WATCALL )
        mov ParamReverse,1
    .endif

    mov edi,[esi].paralist
    .if ( ParamReverse )
        .for ( : edi && [edi].dsym.nextparam : edi = [edi].dsym.nextparam )
        .endf
    .endif
    mov paracurr,edi


    ; v2.11: proc_info.init_done has been removed, sym.isproc flag is used instead

    mov ecx,p
    movzx eax,[ecx].asym.flag1
    and eax,S_ISPROC
    mov init_done,eax

    mov ebx,tokenarray.tokptr(i)
    .for ( cntParam = 0 : [ebx].token != T_FINAL : cntParam++ )

        .if ( [ebx].token == T_ID )
            mov name,[ebx].string_ptr
            inc i
            add ebx,16
        .elseif ( IsPROC == FALSE && [ebx].token == T_COLON )
            .if ( edi )
                mov name,[edi].asym.name
            .else
                mov name,&@CStr("")
            .endif
        .else

            ; PROC needs a parameter name, PROTO accepts <void> also

            .return( asmerr( 2008, [ebx].string_ptr ) )
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


        .if ( [ebx].token != T_COLON )

            .if ( IsPROC == FALSE )
                .return( asmerr( 2065, ":" ) )
            .endif
            mov ti.mem_type,MT_WORD
            .if ( ti.Ofssize != USE16 )
                mov ti.mem_type,MT_DWORD
            .endif

        .else

            inc i
            add ebx,16

            .if ( ( [ebx].token == T_RES_ID ) && ( [ebx].tokval == T_VARARG ) )

                mov ecx,p
                movzx eax,[ecx].asym.langtype

                .switch( eax )
                .case LANG_NONE
                .case LANG_BASIC
                .case LANG_FORTRAN
                .case LANG_PASCAL
                .case LANG_STDCALL
                    .return( asmerr( 2131 ) )
                .endsw

                ; v2.05: added check

                .if ( ( [ebx+16].token == T_FINAL ) || \
                     ( [ebx+16].token == T_STRING && [ebx+16].string_delim == '{' ) )
                    mov is_vararg,TRUE
                .else
                    asmerr( 2129 )
                .endif

                mov ti.mem_type,MT_EMPTY
                mov ti.size,0
                inc i

            .else

                xor eax,eax
                .if ( [ebx].token == T_ID )
                    mov ecx,[ebx].string_ptr
                    mov eax,[ecx]
                    or  eax,0x202020
                .endif
                .if ( eax == 'sba' )
                    mov ti.mem_type,MT_ABS
                    inc i
                .elseif ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                    .return
                .endif
            .endif
        .endif


        ; check if parameter name is defined already

        .if ( IsPROC )
            .if SymSearch( name )
                .if ( [eax].asym.state != SYM_UNDEFINED )
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

            .for ( ecx = ti.symtype : ecx && [ecx].asym.type : ecx = [ecx].asym.type )
            .endf
            mov tn,ecx

            ; v2.12: don't assume pointer type if mem_type is != MT_TYPE!
            ; regression test proc9.asm.
            ; v2.23: proto fastcall :type - fast32.asm

            mov edi,paracurr

            .if ( fastcall_id == FCT_ELF64 + 1 || fastcall_id == FCT_VEC32 + 1 || \
                 fastcall_id == FCT_MSC + 1 )
                mov [edi].asym.target_type,NULL
                .if ( !ModuleInfo.strict_masm_compat )
                    mov fast_type,1 ; v2.27 added
                .endif
            .endif
            .if ( [edi].asym.mem_type == MT_TYPE )
                mov edx,[edi].asym.type
            .else
                xor edx,edx
                .if ( [edi].asym.mem_type == MT_PTR )
                    mov edx,[edi].asym.target_type
                .endif
            .endif
            .for( : edx && [edx].asym.type : edx = [edx].asym.type )
            .endf
            mov to,edx
            mov al,ModuleInfo.Ofssize
            mov ah,al
            .if ( [edi].asym.Ofssize != USE_EMPTY )
                mov al,[edi].asym.Ofssize
            .endif
            mov oo,al
            .if ( ti.Ofssize != USE_EMPTY )
                mov ah,ti.Ofssize
            .endif
            mov on,ah

            .if ( ti.mem_type != [edi].asym.mem_type || \
                ( ti.mem_type == MT_TYPE && tn != to ) || \
                ( ti.mem_type == MT_PTR && ( ti.is_far != [edi].asym.is_far || on != oo || \
                 ( !fast_type && ( ti.ptr_memtype != [edi].asym.ptr_memtype || tn != to ) ) ) ) )
                asmerr( 2111, name )
            .endif
            .if ( IsPROC )

                ; it has been checked already that the name isn't found
                ; - SymAddLocal() shouldn't fail

                SymAddLocal( edi, name )
            .endif

            ; set paracurr to next parameter

            .if ( ParamReverse )
                .for ( ecx = [esi].paralist: ecx && [ecx].dsym.nextparam != edi \
                    : ecx = [ecx].dsym.nextparam )
                .endf
            .else
                mov ecx,[edi].dsym.nextparam
            .endif
            mov paracurr,ecx

        .elseif ( init_done )

            ; second definition has more parameters than first

            .return( asmerr( 2111, "" ) )
        .else
            .if ( IsPROC )
                mov edi,SymLCreate( name )
            .else
                mov edi,SymAlloc( "" )  ; for PROTO, no param name needed
            .endif
            .if ( edi == NULL )         ; error msg has been displayed already
                .return( ERROR )
            .endif
            mov paranode,edi
            or  [edi].asym.flags,S_ISDEFINED
            mov [edi].asym.mem_type,ti.mem_type
            .if ( ti.mem_type == MT_TYPE )
                mov [edi].asym.type,ti.symtype
            .else
                mov [edi].asym.target_type,ti.symtype
            .endif

            ; v2.05: moved BEFORE fastcall_tab()

            mov [edi].asym.is_far,ti.is_far
            mov [edi].asym.Ofssize,ti.Ofssize
            mov [edi].asym.is_ptr,ti.is_ptr
            mov [edi].asym.ptr_memtype,ti.ptr_memtype
            .if ( is_vararg )
                or [edi].asym.sflags,S_ISVARARG
            .endif

            mov eax,fastcall_id
            .if eax
                dec eax
                imul ecx,eax,fastcall_conv
                fastcall_tab[ecx].paramcheck( p, edi, &fcint )
            .endif
            .if ( eax == 0 )
                mov [edi].asym.state,SYM_STACK
            .endif

            mov [edi].asym.total_length,1 ; v2.04: added
            mov [edi].asym.total_size,ti.size

            .if ( !( [edi].asym.sflags & S_ISVARARG ) )

                ; v2.11: CurrWordSize does reflect the default parameter size only for PROCs.
                ;
                ; For PROTOs and TYPEs use member seg_ofssize.

                mov eax,2
                mov ecx,p
                mov cl,[ecx].asym.segoffsize
                shl eax,cl
                .if ( IsPROC )
                    movzx eax,CurrWordSize
                .endif
                mov ecx,ROUND_UP( ti.size, eax )
                add [esi].parasize,ecx
            .endif


            ; Parameters usually are stored in "push" order.
            ; However, for Win64, it's better to store them
            ; the "natural" way from left to right, since the
            ; arguments aren't "pushed".

            mov ecx,p
            movzx eax,[ecx].asym.langtype
            .switch( eax )
            .case LANG_BASIC
            .case LANG_FORTRAN
            .case LANG_PASCAL
            left_to_right:
                mov [edi].dsym.nextparam,NULL
                .if ( [esi].paralist == NULL )
                    mov [esi].paralist,edi
                .else
                    .for ( edx = [esi].paralist: edx: edx = [edx].dsym.nextparam )
                        .break .if ( [edx].dsym.nextparam == NULL )
                    .endf
                    mov [edx].dsym.nextparam,edi
                    mov paracurr,NULL
                .endif
                .endc
            .case LANG_FASTCALL

                ; v2.07: MS fastcall 16-bit is PASCAL!

                .if ( ti.Ofssize == USE16 && ModuleInfo.fctype == FCT_MSC )
                    jmp left_to_right
                .endif
            .default
                mov [edi].dsym.nextparam,[esi].paralist
                mov [esi].paralist,edi
                .endc
            .endsw
        .endif

        mov ebx,tokenarray.tokptr(i)

        .if ( [ebx].token != T_FINAL )
            .if ( [ebx].token != T_COMMA )
                .if ( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_EQU && \
                      [ebx+16].token == T_STRING && [ebx+16].bytval == '<' )

                    mov ecx,[ebx-16].string_ptr
                    mov eax,[ecx]
                    or  eax,0x202020
                    .if ( [ebx-16].token != T_ID || eax != 'sba' )
                        .return( asmerr( 2008, [ebx-16].tokpos ) )
                    .endif
                    add i,2 ; v2.32.16 - name:abs=<val>
                    add ebx,32
                .endif

                mov ecx,tokenarray
                .if ( [ebx].token == T_STRING &&
                      [ebx].string_delim == '{' &&
                      [ecx+16].asm_tok.tokval == T_PROTO )

                    ParseInline(p, ebx, tokenarray)

                .elseif ( [ebx].token != T_COMMA )

                    .return( asmerr( 2065, "," ) )
                .endif
            .endif
            inc i ; go past comma
            add ebx,16
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
        mov ecx,p
        .if ( [ecx].asym.mem_type == MT_FAR )
            inc eax
        .endif
        movzx ecx,CurrWordSize
        mul ecx
        mov offs,eax

        ; now calculate the [E|R]BP offsets

        .for ( : cntParam : cntParam-- )
            .for ( ebx = 1, edi = [esi].paralist: ebx < cntParam : edi = [edi].dsym.nextparam, ebx++ )
            .endf
            .if ( [edi].asym.state != SYM_TMACRO ) ; register param?

                mov   [edi].asym.offs,offs
                or    [esi].flags,PROC_STACKPARAM
                movzx ecx,CurrWordSize
                mov   ebx,ROUND_UP( [edi].asym.total_size, ecx )
                movzx ecx,CurrWordSize

                .if ( ebx > ecx && [edi].asym.mem_type == MT_TYPE )
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

ParseProc proc uses esi edi ebx p:ptr dsym,
        i:int_t, tokenarray:ptr asm_tok, IsPROC:int_t, langtype:byte

  .new token:string_t
  .new regist:ptr word
  .new newmemtype:byte
  .new newofssize:byte
  .new oldofssize:byte
  .new oldpublic:int_t
  .new Ofssize:byte

    mov edi,p
    mov esi,[edi].dsym.procinfo
    movzx eax,[edi].asym.flags
    and eax,S_ISPUBLIC
    mov oldpublic,eax

    ; set some default values

    .if ( IsPROC )

        and [esi].flags,not PROC_ISEXPORT
        .if ( ModuleInfo.procs_export )
            or [esi].flags,PROC_ISEXPORT
        .endif

        ; don't overwrite a PUBLIC directive for this symbol!

        .if ( ModuleInfo.procs_private == FALSE )
            or [edi].asym.flags,S_ISPUBLIC
        .endif

        ; set type of epilog code
        ; v2.11: if base register isn't [E|R]BP, don't use LEAVE!

        mov ebx,ModuleInfo.curr_cpu
        and ebx,P_CPU_MASK
        xor edi,edi
        movzx ecx,[esi].basereg

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
            or [esi].flags,PROC_PE_TYPE
        .endif
    .endif

    ; 1. attribute is <distance>

    mov ebx,tokenarray.tokptr(i)
    .if ( [ebx].token == T_STYPE && \
          [ebx].tokval >= T_NEAR && [ebx].tokval <= T_FAR32 )

        mov Ofssize,GetSflagsSp( [ebx].tokval )
        .if ( IsPROC )
            .if ( ( ModuleInfo.Ofssize >= USE32 && al == USE16 ) || \
                  ( ModuleInfo.Ofssize == USE16 && al == USE32 ) )
                asmerr( 2011 )
            .endif
        .endif

        mov newmemtype,GetMemtypeSp( [ebx].tokval )
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
    mov edi,p
    .if ( [edi].asym.state == SYM_TYPE )
        mov oldofssize,[edi].asym.segoffsize
    .else
        mov oldofssize,GetSymOfssize( edi )
    .endif

    ; did the distance attribute change?

    .if ( [edi].asym.mem_type != MT_EMPTY && \
        ( [edi].asym.mem_type != newmemtype || oldofssize != newofssize ) )
        .if ( [edi].asym.mem_type == MT_NEAR || [edi].asym.mem_type == MT_FAR )
            asmerr( 2112 )
        .else
            .return( asmerr( 2005, [edi].asym.name ) )
        .endif
    .else
        mov [edi].asym.mem_type,newmemtype
        .if ( IsPROC == FALSE )
            mov [edi].asym.segoffsize,newofssize
        .endif
    .endif

    ; 2. attribute is <langtype>
    ; v2.09: the default language value is now a function argument. This is because
    ; EXTERN[DEF] allows to set the language attribute by:
    ; EXTERN[DEF] <langtype> <name> PROTO ...
    ; ( see CreateProto() in extern.asm )

    GetLangType( &i, tokenarray, &langtype ) ; optionally overwrite the value

    ; has language changed?

    .if ( [edi].asym.langtype != LANG_NONE && [edi].asym.langtype != langtype )
        asmerr( 2112 )
    .else
        mov [edi].asym.langtype,langtype
    .endif

    ; 3. attribute is <visibility>
    ; note that reserved word PUBLIC is a directive!
    ; PROTO does NOT accept PUBLIC! However,
    ; PROTO accepts PRIVATE and EXPORT, but these attributes are just ignored!

    mov ebx,tokenarray.tokptr(i)
    .if ( [ebx].token == T_ID || [ebx].token == T_DIRECTIVE )
        mov token,[ebx].string_ptr
        .if ( tstricmp( eax, "PRIVATE") == 0 )
            .if ( IsPROC )  ; v2.11: ignore PRIVATE for PROTO
                and [edi].asym.flags,not S_ISPUBLIC

                ; error if there was a PUBLIC directive!

                or [edi].asym.flags,S_SCOPED
                .if ( oldpublic )
                    SkipSavedState() ; do a full pass-2 scan
                .endif
                and [esi].flags,not PROC_ISEXPORT
            .endif
            inc i
        .elseif ( tstricmp( token, "PUBLIC" ) == 0 )
            .if ( IsPROC )
                or  [edi].asym.flags,S_ISPUBLIC
                and [esi].flags,not PROC_ISEXPORT
            .endif
            inc i
        .elseif ( tstricmp(token, "EXPORT") == 0 )
            .if ( IsPROC )  ;; v2.11: ignore EXPORT for PROTO
                or [edi].asym.flags,S_ISPUBLIC
                or [esi].flags,PROC_ISEXPORT

                ; v2.11: no export for 16-bit near

                .if ( ModuleInfo.Ofssize == USE16 && [edi].asym.mem_type == MT_NEAR )
                    asmerr( 2145, [edi].asym.name )
                .endif
            .endif
            inc i
        .endif
    .endif

    ; 4. attribute is <prologuearg>, for PROC only.
    ; it must be enclosed in <>

    .if ( IsPROC && [ebx].token == T_STRING && [ebx].string_delim == '<' )
        mov edi,Token_Count
        inc edi

        .new max:int_t

        .if ( ModuleInfo.prologuemode == PEM_NONE )

            ; no prologue at all

        .elseif ( ModuleInfo.prologuemode == PEM_MACRO )

            mov ecx,[ebx].stringlen
            inc ecx
            mov ecx,LclAlloc( ecx )
            mov [esi].prologuearg,ecx
            strcpy( ecx, [ebx].string_ptr )

        .else

            ; check the argument. The default prologue
            ;
            ; understands FORCEFRAME and LOADDS only

            mov max,Tokenize( [ebx].string_ptr, edi, tokenarray, TOK_RESCAN )

            .for ( : edi < max: edi++ )

                mov ebx,tokenarray.tokptr(edi)

                .if ( [ebx].token == T_ID )

                    .if ( tstricmp( [ebx].string_ptr, "FORCEFRAME") == 0 )
                        or [esi].flags,PROC_FORCEFRAME
                    .elseif ( ModuleInfo.Ofssize != USE64 && (tstricmp( [ebx].string_ptr, "LOADDS") == 0 ) )
                        .if ( ModuleInfo._model == MODEL_FLAT )
                            asmerr( 8014 )
                        .else
                            or [esi].flags,PROC_LOADDS
                        .endif
                    .else
                        .return( asmerr( 4005, [ebx].string_ptr ) )
                    .endif
                    .if ( [ebx+16].token == T_COMMA && [ebx+32].token != T_FINAL)
                        inc edi
                    .endif
                .else
                    .return( asmerr( 2008, [ebx].string_ptr ) )
                .endif
            .endf
        .endif
        inc i
    .endif

    ; check for optional FRAME[:exc_proc]

    mov ebx,tokenarray.tokptr(i)
    .if ( ModuleInfo.Ofssize == USE64 && IsPROC )

        mov [esi].exc_handler,NULL
        .if ( [ebx].token == T_RES_ID && [ebx].tokval == T_FRAME )
            ;
            ; v2.05: don't accept FRAME for ELF
            ;
            .if ( Options.output_format != OFORMAT_COFF && \
                  ModuleInfo.sub_format != SFORMAT_PE )
                .return( asmerr( 3006, GetResWName( T_FRAME, NULL ) ) )
            .endif
            inc i
            add ebx,asm_tok
            .if ( [ebx].token == T_COLON )
                inc i
                add ebx,asm_tok
                .if ( [ebx].token != T_ID )
                    .return( asmerr(2008, [ebx].string_ptr ) )
                .endif
                mov edi,SymSearch( [ebx].string_ptr )
                .if ( eax == NULL )
                    mov edi,SymCreate( [ebx].string_ptr )
                    mov [eax].asym.state,SYM_UNDEFINED
                    or  [eax].asym.flags,S_USED
                    sym_add_table( &SymTables[TAB_UNDEF*symbol_queue], eax ) ; add UNDEFINED
                .elseif ( [eax].asym.state != SYM_UNDEFINED && \
                       [eax].asym.state != SYM_INTERNAL && \
                       [eax].asym.state != SYM_EXTERNAL )
                    .return( asmerr( 2005, [eax].asym.name ) )
                .endif
                mov [esi].exc_handler,edi
                inc i
                add ebx,asm_tok
            .endif

            or [esi].flags,PROC_ISFRAME
        .elseif ( ModuleInfo.frame_auto == 3 )
            or [esi].flags,PROC_ISFRAME
        .endif
    .endif

    ; check for USES

    .if ( [ebx].token == T_ID )

        mov ecx,[ebx].string_ptr
        mov eax,[ecx]
        or  eax,0x20202020

        .if ( eax == 'sesu' && byte ptr [ecx+4] == 0 )

            .new cnt:int_t
            .new j:int_t
            .new index:int_t
            .new sym:ptr asym

            .if ( !IsPROC ) ; not for PROTO!
                asmerr( 2008, [ebx].string_ptr )
            .endif
            inc i
            add ebx,asm_tok

            ; count register names which follow

            .for ( cnt = 0 : : cnt++, ebx += asm_tok )
                .if ( [ebx].token != T_REG )

                    ; the register may be a text macro here

                    .break .if ( [ebx].token != T_ID )
                    .break .if ( ( SymSearch( [ebx].string_ptr ) ) == NULL )

                    .break .if ( [eax].asym.state != SYM_TMACRO )
                    mov edi,eax
                    mov ecx,FindResWord( [edi].asym.string_ptr, [edi].asym.name_size )
                    imul eax,ecx,special_item
                    .break .if ( SpecialTable[eax].type != RWT_REG )

                    mov [ebx].token,T_REG
                    mov [ebx].tokval,ecx
                    mov [ebx].string_ptr,[edi].asym.string_ptr
                .endif
            .endf
            mov ebx,tokenarray.tokptr(i)

            .if ( cnt == 0 )
                asmerr( 2008, [ebx-16].tokpos )
            .else
                mov  ecx,cnt
                inc  ecx
                imul ecx,ecx,sizeof( uint_16 )
                mov  edi,LclAlloc( ecx )
                mov [esi].regslist,edi
                mov eax,cnt
                stosw

                ; read in registers

                .for ( : [ebx].token == T_REG: i++, ebx += asm_tok )
                    .if ( SizeFromRegister( [ebx].tokval ) == 1 )
                        asmerr( 2032 )
                    .endif
                    mov eax,[ebx].tokval
                    stosw
                .endf
            .endif
        .endif
    .endif

    ; the parameters must follow

    .if ( [ebx].token == T_STYPE || [ebx].token == T_RES_ID || [ebx].token == T_DIRECTIVE )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif

    ; skip optional comma

    .if ( [ebx].token == T_COMMA )
        inc i
        add ebx,asm_tok
    .endif

    mov edi,p
    .if ( i >= Token_Count || \
       ( [ebx].token == T_STRING && [ebx].string_delim == '{' ) )

        ; procedure has no parameters at all

        .if ( [esi].paralist != NULL )
            asmerr( 2111, "" )
        .endif
        .if ( [ebx].token == T_STRING && [ebx].string_delim == '{' )
            ParseInline(edi, ebx, tokenarray)
        .endif

    .elseif ( [edi].asym.langtype == LANG_NONE )
        asmerr( 2119 )
    .else

        ; v2.05: set PROC's vararg flag BEFORE params are scanned!

        mov ebx,Token_Count ; v2.31: proto :vararg {
        dec ebx
        mov ebx,tokenarray.tokptr(ebx)

        .if ( [ebx].token == T_STRING && [ebx].string_delim == '{' )
            sub ebx,asm_tok
        .endif
        .if ( [ebx].token == T_RES_ID && [ebx].tokval == T_VARARG )
            or [esi].flags,PROC_HAS_VARARG
        .endif
        .if ( ParseParams( edi, i, tokenarray, IsPROC ) == ERROR )

            ; do proceed if the parameter scan returns an error
        .endif
    .endif

    ; v2.11: isdefined and isproc now set here

    or [edi].asym.flags,S_ISDEFINED
    or [edi].asym.flag1,S_ISPROC
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

CreateProc proc uses esi edi sym:ptr asym, name:string_t, state:sym_state

    mov eax,sym
    .if ( eax == NULL )
        mov edi,name
        .if ( B[edi] )
            SymCreate( edi )
        .else
            SymAlloc( edi )
        .endif
        mov sym,eax
    .else
        .if ( [eax].asym.state == SYM_UNDEFINED )
            lea ecx,SymTables[TAB_UNDEF*symbol_queue]
        .else
            lea ecx,SymTables[TAB_EXT*symbol_queue]
        .endif
        sym_remove_table( ecx, eax )
    .endif

    mov edi,sym
    .if ( edi )
        mov [edi].asym.state,state
        .if ( state != SYM_INTERNAL )
            mov [edi].asym.segoffsize,ModuleInfo.Ofssize
        .endif
        mov [edi].dsym.procinfo,LclAlloc( sizeof( proc_info ) )
if 0 ; zero alloc..
        xor ecx,ecx
        mov [eax].proc_info.regslist,ecx
        mov [eax].proc_info.paralist,ecx
        mov [eax].proc_info.locallist,ecx
        mov [eax].proc_info.labellist,ecx
        mov [eax].proc_info.parasize,ecx
        mov [eax].proc_info.localsize,ecx
        mov [eax].proc_info.prologuearg,ecx
        mov [eax].proc_info.flags,cl
endif
        .switch ( [edi].asym.state )
        .case SYM_INTERNAL

            ; v2.04: don't use sym_add_table() and thus
            ; free the <next> member field!

            .if ( SymTables[TAB_PROC*symbol_queue].head == NULL )
                mov SymTables[TAB_PROC*symbol_queue].head,edi
            .else
                mov ecx,SymTables[TAB_PROC*symbol_queue].tail
                mov [ecx].dsym.nextproc,edi
            .endif
            mov SymTables[TAB_PROC*symbol_queue].tail,edi
            inc procidx
            .if ( Options.line_numbers )
                mov [edi].asym.debuginfo,LclAlloc( sizeof( debug_info ) )
                get_curr_srcfile()
                mov edx,[edi].asym.debuginfo
                mov [edx].debug_info.file,ax
            .endif
            .endc
        .case SYM_EXTERNAL
            or [edi].asym.sflags,S_WEAK
            sym_add_table( &SymTables[TAB_EXT*symbol_queue], edi )
            .endc
        .endsw
    .endif
    .return( edi )

CreateProc endp

; delete a PROC item

DeleteProc proc uses esi edi p:ptr dsym

    mov edi,p
    .if ( [edi].asym.state == SYM_INTERNAL )

        mov esi,[edi].dsym.procinfo

        ; delete all local symbols ( params, locals, labels )

        .for ( edi = [esi].labellist : edi : )

            mov esi,[edi].dsym.nextll
            SymFree( edi )
            mov edi,esi
        .endf
    .endif
    ret

DeleteProc endp

; PROC directive.

ProcDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local sym:ptr dsym
  local ofs:uint_t
  local name:string_t
  local oldpubstate:int_t
  local is_global:int_t
  local p:ptr proc_info

    mov ebx,tokenarray

    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [ebx+ecx].string_ptr ) )
    .endif

    ; v2.04b: check was missing

    .if ( CurrSeg == NULL )

        ; v2.30.06 - struct proto's ...

        .if ( Parse_Pass == PASS_1 )
            .return( asmerr( 2034 ) )
        .endif
        .return( NOT_ERROR )
    .endif

    mov name,[ebx].string_ptr
    add ebx,asm_tok
    mov edi,CurrProc
    .if ( edi != NULL )

        ; this is not needed for JWasm, but Masm will reject nested
        ; procs if there are params, locals or used registers.

        mov esi,[edi].dsym.procinfo
        .if ( [esi].paralist || \
              [esi].flags & PROC_ISFRAME || \
              [esi].locallist || \
              [esi].regslist )
            .return( asmerr( 2144, name ) )
        .endif

        ; nested procs ... push currproc on a stack

        push_proc( edi )
    .endif


    .if ( ModuleInfo.procalign )
        AlignCurrOffset( ModuleInfo.procalign )
    .endif

    inc i ; go past PROC
    add ebx,asm_tok

    mov sym,SymSearch( name )

    .if ( Parse_Pass == PASS_1 )

        mov oldpubstate,FALSE
        .if ( eax && [eax].asym.flags & S_ISPUBLIC )
            inc oldpubstate
        .endif
        .if ( eax == NULL || [eax].asym.state == SYM_UNDEFINED )
            mov sym,CreateProc( eax, name, SYM_INTERNAL )
            mov is_global,FALSE
        .elseif ( [eax].asym.state == SYM_EXTERNAL && [eax].asym.sflags & S_WEAK )

            ; PROTO or EXTERNDEF item

            mov is_global,TRUE
            .if ( [eax].asym.flag1 & S_ISPROC )

                ; don't create the procinfo extension; it exists already

                inc procidx ; v2.04: added
                .if ( Options.line_numbers )
                    mov edi,LclAlloc( sizeof( debug_info ) )
                    mov ecx,sym
                    mov [ecx].asym.debuginfo,edi
                    mov [edi].debug_info.file,get_curr_srcfile()
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

            mov ecx,sym
            .return( asmerr( 2005, [ecx].asym.name ) )
        .endif
        mov edi,sym
        SetSymSegOfs( edi )
        SymClearLocal()

        ; v2.11: added. Note that fpo flag is only set if there ARE params!

        mov esi,[edi].dsym.procinfo
        movzx ecx,ModuleInfo.Ofssize
        mov ecx,ModuleInfo.basereg[ecx*4]
        mov [esi].basereg,cx

        ; CurrProc must be set, it's used inside SymFind() and SymLCreate()!

        mov CurrProc,edi
        .if ( ParseProc( edi, i, tokenarray, TRUE, ModuleInfo.langtype ) == ERROR )
            mov CurrProc,NULL
            .return( ERROR )
        .endif

        ; v2.04: added

        .if ( is_global && Options.masm8_proc_visibility )
            or [edi].asym.flags,S_ISPUBLIC
        .endif

        ; if there was a PROTO (or EXTERNDEF name:PROTO ...),
        ; change symbol to SYM_INTERNAL!

        .if ( [edi].asym.state == SYM_EXTERNAL && [edi].asym.flag1 & S_ISPROC )
            sym_ext2int( edi )

            ; v2.11: added ( may be better to call CreateProc() - currently not possible )

            .if ( SymTables[TAB_PROC*symbol_queue].head == NULL )
                mov SymTables[TAB_PROC*symbol_queue].head,edi
            .else
                mov ecx,SymTables[TAB_PROC*symbol_queue].tail
                mov [ecx].dsym.nextproc,edi
            .endif
            mov SymTables[TAB_PROC*symbol_queue].tail,edi
        .endif

        ; v2.11: sym->isproc is set inside ParseProc()
        ; v2.11: Note that fpo flag is only set if there ARE params ( or locals )!

        mov ecx,CurrProc
        mov esi,[ecx].dsym.procinfo
        movzx ecx,[esi].basereg
        .if ( [esi].paralist && GetRegNo( ecx ) == 4 )
            or [esi].flags,PROC_FPO
        .endif
        .if ( [edi].asym.flags & S_ISPUBLIC && oldpubstate == FALSE )
            AddPublicData( edi )
        .endif

        ; v2.04: add the proc to the list of labels attached to curr segment.
        ; this allows to reduce the number of passes (see fixup.asm)

        mov ecx,CurrSeg
        mov edx,[ecx].dsym.seginfo
        mov [edi].dsym.next,[edx].seg_info.label_list
        mov [edx].seg_info.label_list,edi

    .else

        ; v2.30.06 - struct proto's ...

        mov edi,sym
        .return( NOT_ERROR ) .if ( edi == NULL )

        inc procidx
        or  [edi].asym.flags,S_ISDEFINED
        SymSetLocal( edi )

        ; it's necessary to check for a phase error here
        ; as it is done in LabelCreate() and data_dir()!

        mov ecx,GetCurrOffset()
        .if ( ecx != [edi].asym.offs )
            mov [edi].asym.offs,ecx
            mov ModuleInfo.PhaseError,TRUE
        .endif
        mov CurrProc,edi

        ; check if the exception handler set by FRAME is defined

        mov esi,[edi].dsym.procinfo
        mov ecx,[esi].exc_handler
        .if ( [esi].flags & PROC_ISFRAME && \
            ecx && [ecx].asym.state == SYM_UNDEFINED )
            asmerr( 2006, [ecx].asym.name )
        .endif
    .endif

    mov ecx,CurrProc
    mov esi,[ecx].dsym.procinfo

    ; v2.11: init @ProcStatus - prologue not written yet, optionally set FPO flag

    mov ecx,PRST_PROLOGUE_NOT_DONE
    .if ( [esi].flags & PROC_FPO )
        or ecx,PRST_FPO
    .endif
    mov ProcStatus,ecx
    mov StackAdj,0  ; init @StackBase to 0
    mov StackAdjHigh,0

    .if ( [esi].flags & PROC_ISFRAME )
        mov endprolog_found,FALSE

        ; v2.11: clear all fields

        memset( &unw_info, 0, sizeof( unw_info ) )
        .if ( [esi].exc_handler )
            unw_info.set_Flags(UNW_FLAG_FHANDLER)
        .endif
    .endif

    mov ecx,sym
    mov [ecx].asym.asmpass,Parse_Pass
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

CopyPrototype proc uses esi edi p:ptr dsym, src:ptr dsym

    mov edi,p
    mov esi,[edi].dsym.procinfo
    mov ecx,src
    .if ( !( [ecx].asym.flag1 & S_ISPROC ) )
        .return( ERROR )
    .endif
    memcpy(esi, [ecx].dsym.procinfo, sizeof( proc_info ) )
    mov ecx,src
    mov [edi].asym.mem_type,[ecx].asym.mem_type
    mov [edi].asym.langtype,[ecx].asym.langtype
    and [edi].asym.flags,not S_ISPUBLIC
    .if ( [ecx].asym.flags & S_ISPUBLIC )
        or [edi].asym.flags,S_ISPUBLIC
    .endif
    ;
    ; we use the PROTO part, not the TYPE part
    ;
    mov [edi].asym.segoffsize,[ecx].asym.segoffsize
    or  [edi].asym.flag1,S_ISPROC
    mov [esi].paralist,NULL

    mov edx,[ecx].dsym.procinfo
    .for ( edi = [edx].proc_info.paralist: edi : edi = [edi].dsym.nextparam )
        memcpy( LclAlloc( sizeof( dsym ) ), edi, sizeof( dsym ) )
        mov [eax].dsym.nextparam,NULL
        .if ( ![esi].paralist )
            mov [esi].paralist,eax
        .else
            .for ( ecx = [esi].paralist : [ecx].dsym.nextparam: ecx = [ecx].dsym.nextparam )
            .endf
            mov [ecx].dsym.nextparam,eax
        .endif
    .endf
    .return( NOT_ERROR )

CopyPrototype endp

;
; for FRAME procs, write .pdata and .xdata SEH unwind information
;

WriteSEHData proc private uses esi edi ebx p:ptr dsym

   .new xdata:ptr dsym
   .new segname:string_t = ".xdata"
   .new i:int_t
   .new simplespec:int_t
   .new olddotname:uchar_t
   .new xdataofs:uint_t = 0
   .new segnamebuff[12]:char_t
   .new buffer[128]:char_t

    mov edi,p
    .if ( endprolog_found == FALSE )
        asmerr( 3007, [edi].asym.name )
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
    .if ( eax )
        ;
        ; v2.11: changed offset to max_offset.
        ; However, value structinfo.current_loc might even be better.
        ;
        mov xdataofs,[eax].asym.max_offset
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
        .for ( edi = &buffer : esi : esi-- )

            lea ebx,[edi+strlen(edi)]
            tsprintf( ebx, "%s 0%xh", pfx, unw_code[esi*2-2].FrameOffset )

            mov pfx,&T(",")
            .if ( esi == 1 || strlen( edi ) > 72 )
                AddLineQueue( edi )
                mov byte ptr [edi],NULLC
                mov pfx,&T("dw")
            .endif
        .endf
    .endif

    ; make sure the unwind codes array has an even number of entries

    AddLineQueue( "ALIGN 4" )

    mov edi,p
    mov esi,[edi].dsym.procinfo
    .if ( [esi].exc_handler )
        mov ecx,[esi].exc_handler
        AddLineQueueX(
            "dd IMAGEREL %s\n"
            "ALIGN 8", [ecx].asym.name )
    .endif
    AddLineQueueX( "%s ENDS", segname )

    ;
    ; v2.07: ensure that .pdata items are sorted
    ;

    SimGetSegName( SIM_CODE )
    mov ecx,[edi].asym.segm
    .if ( !tstrcmp( eax, [ecx].asym.name ) )
        mov segname,&T(".pdata")
        mov al,unw_segs_defined
        and eax,1
        mov simplespec,eax
        mov unw_segs_defined,3
    .else
        mov segname,segnamebuff
        tsprintf( segname, ".pdata$%04u", GetSegIdx( [edi].asym.segm ) )
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
        "%s ENDS", [edi].asym.name, [edi].asym.name, [edi].asym.total_size, xdataofs, segname )
    mov olddotname,ModuleInfo.dotname
    mov ModuleInfo.dotname,TRUE ; set OPTION DOTNAME because .pdata and .xdata
    RunLineQueue()
    mov ModuleInfo.dotname,olddotname
    ret

WriteSEHData endp

;
; close a PROC
;
SetLocalOffsets proto :ptr proc_info

ProcFini proc private uses esi edi p:ptr dsym

    ;
    ; v2.06: emit an error if current segment isn't equal to
    ; the one of the matching PROC directive. Close the proc anyway!
    ;
    mov edi,p
    mov eax,[edi].asym.segm
    .if ( CurrSeg == eax )
        mov ecx,GetCurrOffset()
        sub ecx,[edi].asym.offs
        mov [edi].asym.total_size,ecx
    .else
        asmerr( 1010, [edi].asym.name )
        mov edx,CurrSeg
        mov ecx,[edx].asym.segm
        mov ecx,[ecx].asym.offs
        sub ecx,[edi].asym.offs
        mov [edi].asym.total_size,ecx
    .endif
    ;
    ; v2.03: for W3+, check for unused params and locals
    ;
    mov esi,[edi].dsym.procinfo
    .if ( Options.warning_level > 2 && Parse_Pass == PASS_1 )
        .for ( edi = [esi].paralist: edi: edi = [edi].dsym.nextparam )
            .if ( !( [edi].asym.flags & S_USED ) )
                asmerr( 6004, [edi].asym.name )
            .endif
        .endf
        .for ( edi = [esi].locallist: edi: edi = [edi].dsym.nextlocal )
            .if ( !( [edi].asym.flags & S_USED ) )
                asmerr( 6004, [edi].asym.name )
            .endif
        .endf
    .endif
    ;
    ; save stack space reserved for INVOKE if OPTION WIN64:2 is set
    ;
    .if ( Parse_Pass == PASS_1 && \
         ( ModuleInfo.fctype == FCT_WIN64 || \
           ModuleInfo.fctype == FCT_VEC64 || \
           ModuleInfo.fctype == FCT_ELF64 ) && \ ;; v2.28: added
         ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        mov ecx,sym_ReservedStack
        mov ecx,[ecx].asym.value
        mov [esi].ReservedStack,ecx
        .if ( [esi].flags & PROC_FPO )
            .for ( edi = [esi].locallist: edi: edi = [edi].dsym.nextlocal )
                add [edi].asym.offs,ecx
            .endf
            .for ( edi = [esi].paralist: edi: edi = [edi].dsym.nextparam )
                add [edi].asym.offs,ecx
            .endf
        .endif
    .endif
    ;
    ; create the .pdata and .xdata stuff
    ;
    .if ( [esi].flags & PROC_ISFRAME )
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
            mov ecx,CurrProc
            mov ecx,[ecx].dsym.procinfo
            SetLocalOffsets( ecx )
        .endif
        SymGetLocal( CurrProc )
    .endif

    mov CurrProc,pop_proc()
    .if ( CurrProc )
        SymSetLocal( CurrProc ) ; restore local symbol table
    .endif

    mov ProcStatus,0 ; in case there was an empty PROC/ENDP pair
    ret

ProcFini endp

;
; ENDP directive
;

EndpDir proc uses ebx i:int_t, tokenarray:ptr asm_tok

  local buffer[128]:char_t

    mov ebx,tokenarray
    .if ( i != 1 || [ebx+32].token != T_FINAL )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [ebx+ecx].tokpos ) )
    .endif

    ; v2.30: .return without RET ?

    .if ( ModuleInfo.RetStack )

        AddLineQueueX(
            "org $ - 2\n"  ; skip the last jump
            "ret" )
        RunLineQueue()
    .endif

    ; v2.10: "+ 1" added to CurrProc->sym.name_size

    mov ecx,CurrProc
    .if ( ecx )

        mov edx,[ecx].asym.name_size
        inc edx
        .if ( SymCmpFunc( [ecx].asym.name, [ebx].string_ptr, edx ) == 0 )
            ProcFini( CurrProc )
            mov ecx,1
        .else
            xor ecx,ecx
        .endif
    .endif
    .if ( ecx == 0 )
        .return( asmerr( 1010, [ebx].string_ptr ) )
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

ExcFrameDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

   .new opndx:expr
   .new token:int_t
   .new size:dword
   .new oldcodes:byte = unw_info.CountOfCodes
   .new reg:byte
   .new ofs:byte
   .new puc:ptr UNWIND_CODE

    mov edi,CurrProc
    mov esi,[edi].dsym.procinfo
    mov ebx,tokenarray.tokptr(i)

    ; v2.05: accept directives for windows only

    .if ( Options.output_format != OFORMAT_COFF && ModuleInfo.sub_format != SFORMAT_PE )
        .return( asmerr( 3006, GetResWName( [ebx].tokval, NULL ) ) )
    .endif
    .if ( edi == NULL || endprolog_found == TRUE )
        .return( asmerr( 3008 ) )
    .endif

    .if ( !( [esi].flags & PROC_ISFRAME ) )
        .return( asmerr( 3009 ) )
    .endif

    movzx ecx,unw_info.CountOfCodes
    mov puc,&unw_code[ecx*UNWIND_CODE]
    mov ecx,GetCurrOffset()
    sub ecx,[edi].asym.offs
    mov ofs,cl
    mov token,[ebx].tokval
    inc i
    add ebx,asm_tok

    ; note: since the codes will be written from "right to left",
    ; the opcode item has to be written last!

    .switch ( token )
    .case T_DOT_ALLOCSTACK ; syntax: .ALLOCSTACK size
        .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )

        mov ebx,tokenarray.tokptr(i)
        mov ecx,opndx.sym
        .if ( opndx.kind == EXPR_ADDR && [ecx].asym.state == SYM_UNDEFINED )
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
        sub ecx,[edi].asym.offs
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
        .if ( [ebx].token == T_ID )

            mov ecx,[ebx].string_ptr
            mov eax,[ecx]
            or  eax,0x20202020
            .if ( eax == 'edoc' && byte ptr [ecx+4] == 0 )
                puc.set_OpInfo(1)
                inc i
                add ebx,asm_tok
            .endif
        .endif
        inc unw_info.CountOfCodes
        .endc
    .case T_DOT_PUSHREG ; syntax: .PUSHREG r64
        mov ecx,GetValueSp( [ebx].tokval )
        and ecx,OP_R64
        .if ( [ebx].token != T_REG || !( ecx ) )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        puc.set_CodeOffset(ofs)
        puc.set_UnwindOp(UWOP_PUSH_NONVOL)
        puc.set_OpInfo(GetRegNo( [ebx].tokval ))
        inc unw_info.CountOfCodes
        inc i
        add ebx,asm_tok
        .endc
    .case T_DOT_SAVEREG    ; syntax: .SAVEREG r64, offset
    .case T_DOT_SAVEXMM128 ; syntax: .SAVEXMM128 xmmreg, offset
    .case T_DOT_SETFRAME   ; syntax: .SETFRAME r64, offset
        .if ( [ebx].token != T_REG )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        .if ( token == T_DOT_SAVEXMM128 )
            .if ( !( GetValueSp( [ebx].tokval ) & OP_XMM ) )
                .return( asmerr( 2008, [ebx].string_ptr ) )
            .endif
        .else
            .if ( !( GetValueSp( [ebx].tokval ) & OP_R64 ) )
                .return( asmerr( 2008, [ebx].string_ptr ) )
            .endif
        .endif
        mov reg,GetRegNo( [ebx].tokval )

        .if ( token == T_DOT_SAVEREG )
            mov size,8
        .else
            mov size,16
        .endif

        inc i
        add ebx,asm_tok
        .if ( [ebx].token != T_COMMA )
            .return( asmerr(2008, [ebx].string_ptr ) )
        .endif
        inc i
        .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )

        mov ebx,tokenarray.tokptr(i)
        mov ecx,opndx.sym
        .if ( opndx.kind == EXPR_ADDR && [ecx].asym.state == SYM_UNDEFINED )
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
    .if ( [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].string_ptr ) )
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

ProcCheckOpen proc uses edi
    mov edi,CurrProc
    .while ( edi != NULL )
        asmerr( 1010, [edi].asym.name )
        ProcFini( edi )
        mov edi,CurrProc
    .endw
    ret
ProcCheckOpen endp

write_userdef_prologue proc private uses esi edi ebx tokenarray:ptr asm_tok

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

   .return( NOT_ERROR ) .if ( Parse_Pass > PASS_1 && UseSavedState )

    mov edi,CurrProc
    mov esi,[edi].dsym.procinfo
    movzx ebx,[edi].asym.langtype ; set bits 0-2
    mov info,esi

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

    .if ( [edi].asym.mem_type == MT_FAR )
        or ebx,0x20
    .endif
    .if ( !( [edi].asym.flags & S_ISPUBLIC ) )
        or ebx,0x40
    .endif
    .if ( [esi].flags & PROC_ISEXPORT )
        or ebx,0x80
    .endif
    mov flags,ebx

    mov dir,SymSearch( ModuleInfo.proc_prologue )
    .if ( eax == NULL || [eax].asym.state != SYM_MACRO || !( [eax].asym.mac_flag & M_ISFUNC ) )
        .return( asmerr( 2120 ) )
    .endif

    ; if -EP is on, emit "prologue: none"

    .if ( Options.preprocessor_stdout )
        tprintf( "option prologue:none\n" )
    .endif

    lea edi,reglst
    mov esi,[esi].regslist
    .if ( esi )
        movzx ebx,word ptr [esi]
        .for ( esi += 2: ebx: ebx--, esi += 2 )
            movzx ecx,word ptr [esi]
            GetResWName( ecx, edi )
            add edi,strlen( edi )
            .if ( ebx > 1 )
                mov byte ptr [edi],','
                inc edi
            .endif
        .endf
    .endif
    mov byte ptr [edi],NULLC

    mov esi,info
    mov edi,CurrProc

    ; v2.07: make this work with radix != 10
    ; leave a space at pos 0 of buffer, because the buffer is used for
    ; both macro arguments and EXITM return value.

    mov ecx,[esi].prologuearg
    .if ( !ecx )
        lea ecx,@CStr("")
    .endif

    tsprintf( &buffer," (%s, 0%XH, 0%XH, 0%XH, <<%s>>, <%s>)",
             [edi].asym.name, flags, [esi].parasize, [esi].localsize, &reglst, ecx )

    mov ebx,Token_Count
    inc ebx
    mov Token_Count,Tokenize( &buffer, ebx, tokenarray, TOK_RESCAN )

    RunMacro( dir, ebx, tokenarray, &buffer, 0, &is_exitm )
    dec ebx
    mov Token_Count,ebx

    .if ( Parse_Pass == PASS_1 )

        mov ebx,atoi( &buffer )
        sub ebx,[esi].localsize
        .for ( edi = [esi].locallist: edi: edi = [edi].dsym.nextlocal )
            sub [edi].asym.offs,ebx
        .endf
    .endif
    .return ( NOT_ERROR )

write_userdef_prologue endp

; OPTION WIN64:1 - save up to 4 register parameters for WIN64 fastcall
; v2.27 - save up to 6 register parameters for WIN64 vectorcall
; v2.30 - reverse direction of args + vectorcall stack 8/16

win64_MoveRegParam proc private uses esi edi i:int_t, size:int_t, param:ptr dsym

  local langtype:byte

    mov ecx,CurrProc
    mov langtype,[ecx].asym.langtype
    xor esi,esi
    mov edi,param
    mov al,[edi].asym.mem_type
    .if ( al == MT_TYPE )
        mov edx,[edi].asym.type
        mov al,[edx].asym.mem_type
    .endif
    mov ecx,i
    lea edx,[ecx+T_XMM0]

    .if ( al & MT_FLOAT || al == MT_YWORD || \
          ( langtype == LANG_VECTORCALL && al == MT_OWORD ) )
        .if ( al == MT_REAL4 || al == MT_REAL2 )
            mov esi,T_MOVD
        .elseif ( al == MT_REAL8 )
            mov esi,T_MOVQ
        .elseif ( [edi].asym.total_size <= 16 )
            mov esi,T_MOVAPS
        .elseif ( [edi].asym.total_size == 32 )
            mov esi,T_VMOVUPS
            lea edx,[ecx+T_YMM0]
        .elseif ( [edi].asym.total_size == 64 )
            mov esi,T_VMOVUPS
            lea edx,[ecx+T_ZMM0]
        .endif
    .elseif ( ecx < 4 )
        mov edx,ms64_regs[ecx*4]
        mov esi,T_MOV
    .endif
    .if ( esi )
        imul ecx,size
        add ecx,8
        AddLineQueueX( "%r [%r+%u], %r", esi, T_RSP, ecx, edx )
    .endif
    ret

win64_MoveRegParam endp

win64_GetRegParams proc private uses esi edi ebx varargs:ptr int_t, size:ptr inr_t, param:ptr dsym

    mov esi,size
    mov edi,param
    mov ecx,CurrProc
    mov cl,[ecx].asym.langtype

    .if ( cl == LANG_VECTORCALL )
        mov dword ptr [esi],16
    .else
        mov dword ptr [esi],8
    .endif
    mov edx,varargs
    .if ( edi && [edi].asym.sflags & S_ISVARARG )
        mov dword ptr [edx],1
        .return 4
    .endif
    mov dword ptr [edx],0
    .for ( ebx = 0: edi: edi = [edi].dsym.nextparam )
        mov eax,[esi]
        .if ( [edi].asym.total_size > eax )
            .switch ( [edi].asym.mem_type )  ; limit to float/vector..
            .case MT_REAL10 ; v2.32.32 - REAL10
            .case MT_OWORD
            .case MT_REAL16
                mov dword ptr [esi],16
                .endc
            .case MT_YWORD
                mov dword ptr [esi],32
                .endc
            .case MT_ZWORD
                mov dword ptr [esi],64
                .endc
            .endsw
        .endif
        inc ebx
    .endf
    .return( ebx )

win64_GetRegParams endp

win64_SaveRegParams proc private uses esi edi ebx info:ptr proc_info

   .new size:int_t
   .new varargs:int_t
   .new maxregs:int_t = 4

    mov esi,info
    mov edi,CurrProc
    .if ( [edi].asym.langtype == LANG_VECTORCALL )
        mov maxregs,6
    .endif

    mov edi,[esi].paralist
    mov ebx,win64_GetRegParams( &varargs, &size, edi )
    .while ( ebx > maxregs )
        dec ebx
        .if ( Parse_Pass == PASS_1 && !( [edi].asym.sflags & S_ISVARARG ) && size >= 16 )
            mov eax,size
            mul ebx
            add eax,16
            mov [edi].asym.offs,eax
        .endif
        mov edi,[edi].dsym.nextparam
    .endw
    .fors ( --ebx: edi && ebx >= 0: ebx-- )

        ; v2.05: save XMMx if type is float/double

        .if ( !( [edi].asym.sflags & S_ISVARARG ) )
            .if ( [edi].asym.flags & S_USED || varargs || Parse_Pass == PASS_1 )
                win64_MoveRegParam( ebx, size, edi )
            .endif
            .if ( Parse_Pass == PASS_1 && size >= 16 ) ; v2.30 - update param offset
                mov eax,size
                mul ebx
                add eax,16
                mov [edi].asym.offs,eax
            .endif
            mov edi,[edi].dsym.nextparam
        .elseif ( ebx < 4 )  ; v2.09: else branch added
            mov eax,size
            mul ebx
            add eax,8
            AddLineQueueX( "mov [%r+%u], %r", T_RSP, eax, ms64_regs[ebx*4] )
        .endif
    .endf
    ret
win64_SaveRegParams endp

;
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

write_default_prologue proc private uses esi edi ebx

   .new info:ptr proc_info
   .new regist:ptr word
   .new oldlinenumbers:byte
   .new ppfmt:array_t
   .new cntxmm:int_t
   .new cnt:int_t
   .new offs:int_t
   .new sysstack:int_t = 0
   .new resstack:int_t = 0
   .new cstack:int_t = 0

    mov edi,CurrProc
    movzx ebx,[edi].asym.langtype

    .if ( ( ModuleInfo.xflag & OPT_CSTACK ) && ( ModuleInfo.Ofssize == USE64 ||
          ( ModuleInfo.Ofssize == USE32 && ( ebx == LANG_STDCALL || ebx == LANG_C || ebx == LANG_SYSCALL ) ) ) )
        mov cstack,1
    .endif

    mov esi,[edi].dsym.procinfo
    mov info,esi
    .if ( ModuleInfo.Ofssize == USE64 && [esi].paralist && ebx == LANG_SYSCALL && \
          ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )
        mov sysstack,1
    .endif

    .if ( [esi].flags & PROC_ISFRAME )

        .if ( ModuleInfo.frame_auto & 1 )

            ; win64 default prologue when PROC FRAME and
            ; OPTION FRAME:AUTO is set

            mov resstack,0
            .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
                mov ecx,sym_ReservedStack
                mov resstack,[ecx].asym.value
            .endif

            .if ( ModuleInfo.win64_flags & W64F_SAVEREGPARAMS )
                win64_SaveRegParams( esi )
            .endif

            ; PUSH RBP
            ; .PUSHREG RBP
            ; MOV RBP, RSP
            ; .SETFRAME RBP, 0

            ; Push the registers

            .if ( cstack == 1 )

                mov cntxmm,0
                mov offs,0
                mov esi,[esi].regslist
                .if ( esi )
                    lodsw
                    movzx ebx,ax
                    .for ( : ebx: ebx--, esi += 2 )
                        movzx edi,word ptr [esi]
                        .if ( GetValueSp( edi ) & OP_XMM )
                            inc cntxmm
                        .else
                            add offs,8
                            AddLineQueueX( " push %r", edi )
                            mov cl,GetRegNo( edi )
                            mov eax,1
                            shl eax,cl
                            .if ( ax & win64_nvgpr )
                                AddLineQueueX( " %r %r", T_DOT_PUSHREG, edi )
                            .endif
                        .endif
                    .endf

                    mov esi,info
                    .for ( edi = [esi].paralist: edi: edi = [edi].dsym.nextparam )
                        .break .if ( ![edi].dsym.nextparam )
                    .endf

                    .if ( edi )

                        ; v2.23 - skip adding if stackbase is not EBP

                        movzx ecx,ModuleInfo.Ofssize
                        mov ecx,ModuleInfo.basereg[ecx*4]
                        .if ( ( [edi].asym.offs == 8 && ecx == T_EBP ) || \
                              ( [edi].asym.offs == 16 && ecx == T_RBP ) )
                            .for ( edi = [esi].paralist: edi: edi = [edi].dsym.nextparam )
                                .if ( [edi].asym.state != SYM_TMACRO )
                                    add [edi].asym.offs,offs
                                .endif
                            .endf
                        .endif
                    .endif
                .endif
            .endif

            ; info->locallist tells whether there are local variables ( info->localsize doesn't! )

            mov esi,info
            .if ( [esi].flags & PROC_FPO || ( [esi].parasize == 0 && [esi].locallist == NULL ) )
            .else
                movzx ebx,[esi].basereg
                AddLineQueueX(
                    " push %r\n"
                    " %r %r\n"
                    " mov %r, %r\n"
                    " %r %r, 0", ebx, T_DOT_PUSHREG, ebx, ebx, T_RSP, T_DOT_SETFRAME, ebx )
            .endif

            ; after the "push rbp", the stack is xmmword aligned

            ; Push the registers

            .if ( cstack == 0 )
                mov cntxmm,0
                mov esi,[esi].regslist
                .if ( esi )
                    lodsw
                    movzx ebx,ax
                    .for ( : ebx: ebx--, esi += 2 )
                        movzx edi,word ptr [esi]
                        .if ( GetValueSp( edi ) & OP_XMM )
                            inc cntxmm
                        .else
                            AddLineQueueX( " push %r", edi )
                            mov cl,GetRegNo( edi )
                            mov eax,1
                            shl eax,cl
                            .if ( ax & win64_nvgpr )
                                AddLineQueueX( " %r %r", T_DOT_PUSHREG, edi )
                            .endif
                        .endif
                    .endf
                .endif
            .endif

            ; alloc space for local variables

            mov esi,info
            mov ebx,[esi].localsize
            add ebx,resstack
            .if ( ebx )

                ;
                ; SUB RSP, localsize
                ; .ALLOCSTACK localsize
                ;
                lea edi,fmtstk0
                .if ( resstack )
                    lea edi,fmtstk1
                .endif
                mov ecx,sym_ReservedStack
if STACKPROBE
                .if ( Options.chkstack && ebx > 0x1000 )

                    AddLineQueueX( [edi+2*4], T_RAX, [esi].localsize, [ecx].asym.name )
                    AddLineQueueX(
                        " externdef _chkstk:PROC\n"
                        " call _chkstk\n"
                        " sub rsp, rax" )
                .else
endif
                    AddLineQueueX( [edi], T_RSP, [esi].localsize, [ecx].asym.name )
if STACKPROBE
                .endif
endif
                mov ecx,sym_ReservedStack
                AddLineQueueX( [edi+1*4], T_DOT_ALLOCSTACK, [esi].localsize, [ecx].asym.name )

                ; save xmm registers

                .if ( cntxmm )

                   .new i:int_t
                   .new cnt:int_t

                    imul ecx,cntxmm,16
                    mov eax,[esi].localsize
                    sub eax,ecx
                    and eax,not (16-1)
                    mov i,eax
                    mov esi,[esi].regslist
                    lodsw
                    movzx ebx,ax
                    .for ( : ebx: ebx--, esi += 2 )
                        movzx edi,word ptr [esi]
                        .if ( GetValueSp( edi ) & OP_XMM )
                            .if ( resstack )
                                mov ecx,sym_ReservedStack
                                AddLineQueueX( "movdqa [%r+%u+%s], %r", T_RSP, i, [ecx].asym.name, edi )
                                mov cl,GetRegNo( edi )
                                mov eax,1
                                shl eax,cl
                                .if ( ax & win64_nvxmm )
                                    mov ecx,sym_ReservedStack
                                    AddLineQueueX( "%r %r, %u+%s", T_DOT_SAVEXMM128, edi, i, [ecx].asym.name )
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
    mov esi,info
    .if ( ModuleInfo.Ofssize == USE64 && ( ModuleInfo.fctype == FCT_WIN64 || \
          ModuleInfo.fctype == FCT_VEC64 || ModuleInfo.fctype == FCT_ELF64 ) && \
          ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        mov ecx,sym_ReservedStack
        .if ( ModuleInfo.fctype == FCT_ELF64 && [esi].flags & PROC_HAS_VARARG )
            mov [ecx].asym.value,208
        .endif
        mov resstack,[ecx].asym.value
    .endif

    ; default processing. if no params/locals are defined, continue

    .if ( !( [esi].flags & ( PROC_FORCEFRAME or PROC_STACKPARAM or PROC_HAS_VARARG ) ) && \
          [esi].localsize == 0 && sysstack == 0 && resstack == 0 && [esi].regslist == NULL )

        .return( NOT_ERROR )
    .endif

    mov regist,[esi].regslist

    ; initialize shadow space for register params

    mov ecx,CurrProc
    movzx ecx,[ecx].asym.langtype
    .if ( ModuleInfo.Ofssize == USE64 && ( ecx == LANG_FASTCALL || ecx == LANG_VECTORCALL ) )

        .if ( ModuleInfo.win64_flags & W64F_SAVEREGPARAMS )
            win64_SaveRegParams( esi )
        .elseif ( ModuleInfo.fctype == FCT_VEC64 && Parse_Pass == PASS_1 )

            ; set param offset to 16

            .for ( ebx = 0, ecx = 16,
                   edx = [esi].paralist: edx: edx = [edx].dsym.nextparam, ebx++, ecx += 16 )
                .break .if ( ![edx].dsym.nextparam )
            .endf
            .for ( edx = [esi].paralist: edx && ebx: edx = [edx].dsym.nextparam, ebx--, ecx -= 16 )
                mov [edx].asym.offs,ecx
            .endf
        .endif
    .endif

    ; Push the USES registers first if -Cs

    .if ( regist && cstack )

        mov offs,0
        mov edi,regist
        movzx ebx,word ptr [edi]
        .for ( edi += 2 : ebx : ebx--, edi += 2 )
            movzx edx,word ptr [edi]
            movzx eax,ModuleInfo.Ofssize
            shl eax,2
            add offs,eax
            AddLineQueueX( " push %r", edx )
        .endf
        mov regist,NULL

        .for ( edi = [esi].paralist: edi: edi = [edi].dsym.nextparam )
            .break .if ( ![edi].dsym.nextparam )
        .endf

        .if ( edi )

            ; v2.23 - skip adding if stackbase is not EBP

            movzx ecx,ModuleInfo.Ofssize
            mov ecx,ModuleInfo.basereg[ecx*4]
            .if ( ( [edi].asym.offs == 8 && ecx == T_EBP ) || \
                  ( [edi].asym.offs == 16 && ecx == T_RBP ) )
                .for ( edi = [esi].paralist: edi: edi = [edi].dsym.nextparam )
                    .if ( [edi].asym.state != SYM_TMACRO )
                        add [edi].asym.offs,offs
                    .endif
                .endf
            .endif
        .endif
    .endif

    .if ( sysstack || [esi].locallist || \
          [esi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) )

        ; write 80386 prolog code
        ; PUSH [E|R]BP
        ; MOV [E|R]BP, [E|R]SP
        ; SUB [E|R]SP, localsize

        .if ( !( [esi].flags & PROC_FPO ) )

            movzx ebx,[esi].basereg
            AddLineQueueX( " push %r", ebx )
            movzx ecx,ModuleInfo.Ofssize
            AddLineQueueX( " mov %r, %r", ebx, stackreg[ecx*4] )
        .endif
    .endif

    .if ( resstack )

        ; in this case, push the USES registers BEFORE the stack space is reserved

        .if ( regist )
            mov edi,regist
            movzx ebx,word ptr [edi]
            .for ( edi += 2 : ebx : ebx--, edi += 2 )
                movzx edx,word ptr [edi]
                AddLineQueueX( "push %r", edx )
            .endf
            mov regist,NULL
        .endif

if STACKPROBE
        lea edi,fmtstk0
        .if ( resstack )
            lea edi,fmtstk1
        .endif
        mov ebx,[esi].localsize
        add ebx,resstack
        mov ecx,sym_ReservedStack
        .if ( Options.chkstack && ebx > 0x1000 )

            AddLineQueueX( [edi+2*4], T_RAX, [esi].localsize, [ecx].asym.name )
            AddLineQueueX(
                " externdef _chkstk:PROC\n"
                " call _chkstk\n"
                " sub rsp, rax" )
        .else
endif
        movzx ecx,ModuleInfo.Ofssize
        mov ebx,stackreg[ecx*4]
        mov ecx,sym_ReservedStack
        .if ( ModuleInfo.epilogueflags )
            AddLineQueueX( "lea %r,[%r-(%d + %s)]", ebx, ebx, [esi].localsize, [ecx].asym.name )
        .else
            AddLineQueueX( "sub %r, %d + %s", ebx, [esi].localsize, [ecx].asym.name )
        .endif
if STACKPROBE
        .endif
endif

    .elseif ( [esi].localsize )

        ; using ADD and the 2-complement has one advantage:
        ; it will generate short instructions up to a size of 128.
        ; with SUB, short instructions work up to 127 only.

        movzx ecx,ModuleInfo.Ofssize
        mov ebx,stackreg[ecx*4]
if STACKPROBE
        .if ( Options.chkstack && [esi].localsize > 0x1000 )
            AddLineQueueX(
                "externdef _chkstk:PROC\n"
                "mov eax, %d\n"
                "call _chkstk", [esi].localsize )
            .if ( ModuleInfo.Ofssize == USE64 )
                AddLineQueueX( "sub %r, rax", ebx )
            .endif
        .else
endif
        xor ecx,ecx
        sub ecx,[esi].localsize
        .if ( ModuleInfo.epilogueflags )
            AddLineQueueX( "lea %r, [%r-%d]", ebx, ebx, ecx )
        .elseif ( Options.masm_compat_gencode || [esi].localsize == 128 )
            AddLineQueueX( "add %r, %d", ebx, ecx )
        .else
            AddLineQueueX( "sub %r, %d", ebx, [esi].localsize )
        .endif
if STACKPROBE
        .endif
endif
    .endif

    .if ( [esi].flags & PROC_LOADDS )
        AddLineQueueX(
            "push ds\n"
            "mov ax, %s", &szDgroup )
        mov eax,T_AX
        .if ( ModuleInfo.Ofssize )
            mov eax,T_EAX
        .endif
        AddLineQueueX( "mov ds, %r", eax )
    .endif

    ; Push the USES registers first if stdcall-32
    ; Push the GPR registers of the USES clause

    .if ( regist && cstack == 0 )
        mov edi,regist
        movzx ebx,word ptr [edi]
        .for ( edi += 2 : ebx : ebx--, edi += 2 )
            movzx edx,word ptr [edi]
            AddLineQueueX( " push %r", edx )
        .endf
    .endif

runqueue:

    .if ( ModuleInfo.Ofssize == USE64 && ModuleInfo.fctype == FCT_ELF64 && \
         [esi].flags & PROC_HAS_VARARG && ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        .for ( ebx = 0, edi = [esi].paralist: edi: edi = [edi].dsym.nextparam, ebx++ )
            .break .if ( ![edi].dsym.nextparam )
        .endf

        AddLineQueueX(
            " mov DWORD PTR [rsp+8], %d\n"
            " mov DWORD PTR [rsp+12], 48", &[ebx*8] )
        .for ( : ebx < 6: ebx++ )
            movzx ecx,elf64_regs[ebx+18]
            AddLineQueueX( " mov [rsp+%d+32], %r", &[ebx*8], ecx )
        .endf
        AddLineQueueX( ".if al" )
        .for ( ebx = 0, edi = 80: ebx < 8: ebx++, edi += 16 )
            AddLineQueueX( " movaps [rsp+%d], %r", edi, &[ebx+T_XMM0] )
        .endf
        AddLineQueueX(
            ".endif\n"
            " lea rax, [rsp+224]\n"
            " mov [rsp+16], rax\n"
            " lea rax, [rsp+32]\n"
            " mov [rsp+24], rax\n"
            " lea rax, [rsp+8]" )
    .endif

    ; special case: generated code runs BEFORE the line.

    .if ( ModuleInfo.list && UseSavedState )
        .if ( Parse_Pass > PASS_1 )
            mov list_pos,[esi].prolog_list_pos
        .else
            mov [esi].prolog_list_pos,list_pos
        .endif
    .endif

    ; line number debug info also needs special treatment
    ; because current line number is the first true src line
    ; IN the proc.

    mov oldlinenumbers,Options.line_numbers
    mov Options.line_numbers,FALSE; ;; temporarily disable line numbers
    RunLineQueue()
    mov Options.line_numbers,oldlinenumbers

    .if ( ModuleInfo.list && UseSavedState && ( Parse_Pass > PASS_1 ) )
         mov ecx,LineStoreCurr
         mov [ecx].line_item.list_pos,list_pos
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

SetLocalOffsets proc uses esi edi ebx info:ptr proc_info

   .new curr:ptr dsym
   .new cntxmm:int_t = 0
   .new cntstd:int_t = 0
   .new start:int_t = 0
   .new regsize:int_t = 0 ; v2.25 - option cstack:on
   .new rspalign:int_t = FALSE
   .new calign:int_t = CurrWordSize
   .new wsize:int_t = CurrWordSize

    .if ( ModuleInfo.fctype == FCT_VEC64 )
        mov wsize,16
    .endif

    mov esi,info
    .if ( [esi].flags & PROC_ISFRAME || ( ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) && \
        ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 || \
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

    .if ( [esi].flags & PROC_FPO || rspalign )

        ; count registers to be saved ABOVE local variables.
        ; v2.06: the list may contain xmm registers, which have size 16!

        .if ( [esi].regslist )

            mov edi,[esi].regslist
            movzx ebx,word ptr [edi]
            .for ( edi += 2 : ebx : ebx--, edi += 2 )
                movzx edx,word ptr [edi]
                .if ( GetValueSp( edx ) & OP_XMM )
                    inc cntxmm
                .else
                    inc cntstd
                .endif
            .endf
        .endif

        ; in case there's no frame register, adjust start offset.

        .if ( ( [esi].flags & PROC_FPO || ( [esi].parasize == 0 && [esi].locallist == NULL ) ) )
            mov start,CurrWordSize
        .endif
        .if ( rspalign )
            mov eax,cntstd
            mul wsize
            add eax,start
            mov [esi].localsize,eax
            .if ( cntxmm )
                imul eax,cntxmm,16
                add [esi].localsize,eax
                mov [esi].localsize,ROUND_UP( [esi].localsize, 16 )
            .endif
        .endif
    .endif

    movzx ecx,ModuleInfo.Ofssize
    mov ecx,ModuleInfo.basereg[ecx*4]

    .if ( ( ModuleInfo.xflag & OPT_CSTACK ) && ( ecx == T_RBP || ecx == T_EBP ) )

        imul ecx,cntxmm,16
        mov eax,wsize
        mul cntstd
        add eax,ecx
        mov regsize,eax
    .endif

    ; scan the locals list and set member sym.offset

    .for ( edi = [esi].locallist: edi: edi = [edi].dsym.nextlocal )

        xor eax,eax
        .if ( [edi].asym.total_size )
            mov eax,[edi].asym.total_size
            cdq
            div [edi].asym.total_length
        .endif
        mov ecx,eax
        add [esi].localsize,[edi].asym.total_size
        .if ( ecx > calign )
            mov [esi].localsize,ROUND_UP( [esi].localsize, calign )
        .elseif ( ecx ) ;; v2.04: skip if size == 0
            mov [esi].localsize,ROUND_UP( [esi].localsize, ecx )
        .endif
        mov eax,[esi].localsize
        neg eax
        add eax,regsize
        mov [edi].asym.offs,eax
    .endf

    ; v2.11: localsize must be rounded before offset adjustment if fpo

    mov [esi].localsize,ROUND_UP( [esi].localsize, wsize )

    ; RSP 16-byte alignment?

    .if ( rspalign )
        mov [esi].localsize,ROUND_UP( [esi].localsize, 16 )
    .endif

    ; v2.11: recalculate offsets for params and locals if there's no frame pointer.
    ; Problem in 64-bit: option win64:2 triggers the "stack space reservation" feature -
    ; but the final value of this space is known at the procedure's END only.
    ; Hence in this case the values calculated below are "preliminary".

    .if ( [esi].flags & PROC_FPO )

        movzx edi,CurrWordSize
        .if ( rspalign )
            mov ecx,[esi].localsize
            mov ebx,ecx
            sub ebx,edi
            sub ebx,start
        .else
            mov eax,cntstd
            mul edi
            mov ecx,[esi].localsize
            add ecx,eax
            mov ebx,ecx
            sub ebx,edi
        .endif

        ; subtract CurrWordSize value for params, since no space is required
        ; to save the frame pointer value

        .for ( edi = [esi].locallist: edi: edi = [edi].dsym.nextlocal )
            add [edi].asym.offs,ecx
        .endf
        .for ( edi = [esi].paralist: edi: edi = [edi].dsym.nextparam )
            ; added v2.33.25
            .if ( [edi].asym.state != SYM_TMACRO )
                add [edi].asym.offs,ebx
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
        sub [esi].localsize,eax
    .endif
    ret

SetLocalOffsets endp

write_prologue proc uses esi edi tokenarray:ptr asm_tok

    mov edi,CurrProc
    mov esi,[edi].dsym.procinfo

    ; reset @ProcStatus flag

    and ProcStatus,not PRST_PROLOGUE_NOT_DONE

    .if ( ( ModuleInfo.fctype == FCT_WIN64 || \
            ModuleInfo.fctype == FCT_VEC64 || \
            ModuleInfo.fctype == FCT_ELF64 ) && \
          ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        ; in pass one init reserved stack with 4*8 to force stack frame creation

        mov ecx,sym_ReservedStack
        movzx edx,[edi].asym.langtype
        .if ( Parse_Pass == PASS_1 )
            mov [ecx].asym.value,4 * sizeof( uint_64 )
            .if ( edx == LANG_SYSCALL )
                mov [ecx].asym.value,0
            .elseif ( edx == LANG_VECTORCALL )
                mov [ecx].asym.value,6 * 16
            .endif
        .else
            mov [ecx].asym.value,[esi].ReservedStack
        .endif
    .endif

    .if ( Parse_Pass == PASS_1 )

        ; v2.12: calculation of offsets of local variables is done delayed now

        SetLocalOffsets( esi )
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
    sub ecx,[edi].asym.offs
    mov [esi].size_prolog,cl
    ret

write_prologue endp

pop_register proc private uses esi edi regist:ptr word

    ; Pop the register when a procedure ends

    mov esi,regist
    .return .if ( esi == NULL )

    movzx edi,word ptr [esi]
    lea esi,[esi+edi*2]
    .for ( : edi: edi--, esi -= 2 )

        ; don't "pop" xmm registers

        movzx ecx,word ptr [esi]
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

write_default_epilogue proc private uses esi edi ebx

   .new info:ptr proc_info
   .new sysstack:int_t = 0
   .new leav:int_t = 0
   .new resstack:int_t = 0
   .new cstack:int_t = 0
   .new sreg:int_t

    mov edi,CurrProc
    movzx ecx,[edi].asym.langtype

    .if ( ( ModuleInfo.xflag & OPT_CSTACK ) && ( ModuleInfo.Ofssize == USE64 ||
          ( ModuleInfo.Ofssize == USE32 && ( ecx == LANG_STDCALL || ecx == LANG_C || ecx == LANG_SYSCALL ) ) ) )
        mov cstack,1
    .endif

    mov esi,[edi].dsym.procinfo
    mov info,esi
    .if ( ModuleInfo.Ofssize == USE64 && [esi].paralist && ecx == LANG_SYSCALL && \
          ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )
        inc sysstack
    .endif

    .if ( [esi].locallist || sysstack || \
          [esi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) )
        inc leav
    .endif

    movzx ecx,ModuleInfo.Ofssize
    mov sreg,stackreg[ecx*4]

    .if ( [esi].flags & PROC_ISFRAME )

        .if ( ModuleInfo.frame_auto & 1 )

            ; Win64 default epilogue if PROC FRAME and OPTION FRAME:AUTO is set

            ; restore non-volatile xmm registers

            .if ( [esi].regslist )

                ; v2.12: space for xmm saves is now included in localsize
                ; so first thing to do is to count the xmm regs that were saved

                mov edi,[esi].regslist
                movzx ebx,word ptr [edi]

                .for ( edi += 2, ecx = 0: ebx: ebx--, edi += 2 )
                    movzx eax,word ptr [edi]
                    .if ( GetValueSp( eax ) & OP_XMM )
                        inc ecx
                    .endif
                .endf

                .if ( ecx )

                    imul ecx,ecx,16
                    mov ebx,[esi].localsize
                    sub ebx,ecx
                    and ebx,not (16-1)

                    mov edi,[esi].regslist
                    movzx esi,word ptr [edi]

                    .for ( edi += 2 : esi: esi--, edi += 2 )

                        movzx ecx,word ptr [edi]

                        .if ( GetValueSp( ecx ) & OP_XMM )

                            ; v2.11: use @ReservedStack only if option win64:2 is set

                            .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
                                mov edx,sym_ReservedStack
                                AddLineQueueX( "movdqa %r, [%r + %u + %s]", ecx, sreg, ebx, [edx].asym.name )
                            .else
                                AddLineQueueX( "movdqa %r, [%r + %u]", ecx, sreg, ebx )
                            .endif
                            add ebx,16
                        .endif
                    .endf
                .endif
            .endif

            mov esi,info

            .if ( ( leav && [esi].flags & PROC_PE_TYPE ) && ( cstack || \
                ( ( sysstack || ![esi].regslist ) && [esi].basereg == T_RBP ) ) )

                .if ( cstack == 0 )
                    pop_register( [esi].regslist )
                .endif

                .if ( ( !sysstack && [esi].locallist == NULL ) && \
                      !( [esi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) ) && \
                      resstack == 0 )

                    .if ( cstack )
                        pop_register( [esi].regslist )
                    .endif
                    .return
                .endif

                AddLineQueue( "leave" )
                .if ( cstack )
                    pop_register( [esi].regslist )
                .endif

            .else
                mov ebx,sreg
                .if ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) && \
                      ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )
                    mov edx,sym_ReservedStack
                    .if ( ModuleInfo.epilogueflags )
                        AddLineQueueX( "lea %r, [%r + %d + %s]", ebx,
                            ebx, [esi].localsize, [edx].asym.name )
                    .else
                        AddLineQueueX( "add %r, %d + %s", ebx, [esi].localsize, [edx].asym.name )
                    .endif
                .else
                    .if ( ModuleInfo.epilogueflags )
                        AddLineQueueX( "lea %r, [%r+%d]", ebx, ebx, [esi].localsize )
                    .elseif ( [esi].localsize )
                        AddLineQueueX( "add %r, %d", ebx, [esi].localsize )
                    .endif
                .endif
                .if ( cstack == 0 )
                    pop_register( [esi].regslist )
                .endif
                movzx ecx,[esi].basereg
                .if ( ( GetRegNo( ecx ) != 4 && ( [esi].parasize != 0 || [esi].locallist != NULL ) ) )
                    AddLineQueueX( "pop %r", ecx )
                .endif
                .if ( cstack )
                    pop_register( [esi].regslist )
                .endif
            .endif
        .endif
        .return
    .endif

    .if ( ModuleInfo.Ofssize == USE64 && ( ModuleInfo.fctype == FCT_WIN64 || \
          ModuleInfo.fctype == FCT_VEC64 || ModuleInfo.fctype == FCT_ELF64 ) && \
          ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

        mov ecx,sym_ReservedStack
        mov resstack,[ecx].asym.value

        ; if no framepointer was pushed, add 8 to align stack on OWORD
        ; v2.12: obsolete; localsize contains correct value.

        .if ( cstack && leav && [esi].flags & PROC_PE_TYPE )

            ; v2.21: leave will follow..

        .elseif ( !cstack && leav && [esi].flags & PROC_PE_TYPE &&
                  ( sysstack || ![esi].regslist ) && [esi].basereg == T_RBP )

            ; v2.27: leave will follow..

        .elseif ( resstack || [esi].localsize )
            mov ebx,sreg
            mov edx,sym_ReservedStack
            .if ( ModuleInfo.epilogueflags )
                AddLineQueueX( "lea %r, [%r + %d + %s]", ebx, ebx, [esi].localsize, [edx].asym.name )
            .else
                AddLineQueueX( "add %r, %d + %s", ebx, [esi].localsize, [edx].asym.name )
            .endif
        .endif
    .endif

    .if ( cstack == 0 )

        ; Pop the registers

        pop_register( [esi].regslist )

        .if ( [esi].flags & PROC_LOADDS )
            AddLineQueue( "pop ds" )
        .endif
    .endif

    .if ( ( !sysstack && [esi].locallist == NULL ) &&
          !( [esi].flags & ( PROC_STACKPARAM or PROC_HAS_VARARG or PROC_FORCEFRAME ) ) && \
          resstack == 0 )

        .if ( cstack )

            ; Pop the registers

            pop_register( [esi].regslist )
            .if ( [esi].flags & PROC_LOADDS )
                AddLineQueue( "pop ds" )
            .endif
        .endif
        .return
    .endif

    ; restore registers e/sp and e/bp.
    ; emit either "leave" or "mov e/sp,e/bp, pop e/bp".

    .if ( !leav )

    .elseif( [esi].flags & PROC_PE_TYPE )

        AddLineQueue( "leave" )
    .else

        .if ( [esi].flags & PROC_FPO )
            .if ( ModuleInfo.Ofssize == USE64 && \
                ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) && \
                ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )

            .elseif ( [esi].localsize )
                .if ( ModuleInfo.epilogueflags )
                    AddLineQueueX( "lea %r, [%r+%d]", sreg, sreg, [esi].localsize )
                .else
                    AddLineQueueX( "add %r, %d", sreg, [esi].localsize )
                .endif
            .endif
        .else

            ; MOV [E|R]SP, [E|R]BP
            ; POP [E|R]BP

            .if ( [esi].localsize != 0 )
                AddLineQueueX( "mov %r, %r", sreg, [esi].basereg )
            .endif
            AddLineQueueX( "pop %r", [esi].basereg )
        .endif
    .endif

    .if ( cstack )

        ; Pop the registers

        pop_register( [esi].regslist )

        .if ( [esi].flags & PROC_LOADDS )
            AddLineQueue( "pop ds" )
        .endif
    .endif
    ret

write_default_epilogue endp

;
; write userdefined epilogue code
; if a RET/IRET instruction has been found inside a PROC.
;

write_userdef_epilogue proc private uses esi edi ebx flag_iret:int_t, tokenarray:ptr asm_tok

    mov edi,CurrProc
    mov esi,[edi].dsym.procinfo
    movzx ebx,[edi].asym.langtype

   .new regs:ptr word
   .new i:int_t
   .new p:string_t
   .new is_exitm:int_t
   .new info:ptr proc_info = esi
   .new flags:int_t
   .new dir:ptr dsym
   .new reglst[128]:char_t
   .new buffer[MAX_LINE_LEN]:char_t ; stores string for RunMacro()

    mov dir,SymSearch( ModuleInfo.proc_epilogue )
    .if ( eax == NULL || [eax].asym.state != SYM_MACRO || [eax].asym.mac_flag & M_ISFUNC )
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

    .if ( [edi].asym.mem_type == MT_FAR )
        or edx,0x20
    .endif
    .if ( !( [edi].asym.flags & S_ISPUBLIC ) )
        or edx,0x40
    .endif

    ; v2.11: set bit 7, the export flag

    .if ( [esi].flags & PROC_ISEXPORT )
        or edx,0x80
    .endif
    .if ( flag_iret )
        or edx,0x100 ; bit 8: 1 if IRET
    .endif
    mov flags,edx

    mov edi,[esi].regslist
    lea esi,reglst
    .if ( edi )
        movzx ebx,word ptr [edi]
        lea edi,[edi+ebx*2]
        .for ( : ebx: edi -= 2, ebx-- )
            movzx edx,word ptr [edi]
            GetResWName( edx, esi )
            add esi,strlen( esi )
            .if ( ebx != 1 )
                mov byte ptr [esi],','
                inc esi
            .endif
        .endf
    .endif
    mov byte ptr [esi],NULLC

    mov esi,info
    mov edi,CurrProc
    lea ecx,@CStr("")
    .if ( [esi].prologuearg )
        mov ecx,[esi].prologuearg
    .endif
    tsprintf( &buffer,"%s, 0%XH, 0%XH, 0%XH, <<%s>>, <%s>",
            [edi].asym.name, flags, [esi].parasize, [esi].localsize, &reglst, ecx )

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

RetInstr proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok, count:int_t

   .new info:ptr proc_info
   .new is_iret:int_t = FALSE
   .new p:string_t
   .new buffer[MAX_LINE_LEN]:char_t ; stores modified RETN/RETF/IRET instruction

    mov ebx,tokenarray.tokptr(i)
    .if ( [ebx].tokval == T_IRET || [ebx].tokval == T_IRETD || [ebx].tokval == T_IRETQ )
        mov is_iret,TRUE
    .elseif ( [ebx].tokval == T_RET && ModuleInfo.RetStack )
        mov ecx,ModuleInfo.RetStack
        mov ecx,[ecx].hll_item.labels[LEXIT*4]
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
            mov ecx,LineStoreCurr
            mov [ecx].line_item.line,';'
        .endif
        .return( write_userdef_epilogue( is_iret, tokenarray ) )
    .endif

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL )
    .endif

    mov edi,strcpy( &buffer, [ebx].string_ptr )
    add edi,strlen( eax )

    write_default_epilogue()

    mov ecx,CurrProc
    mov esi,[ecx].dsym.procinfo

    ;
    ; skip this part for IRET
    ;
    .if ( is_iret == FALSE )
        .if ( [ecx].asym.mem_type == MT_FAR )
            mov al,'f' ; ret -> retf
        .else
            mov al,'n' ; ret -> retn
        .endif
        stosb
    .endif

    inc i ; skip directive
    add ebx,asm_tok
    mov edx,count

    .if ( [esi].parasize || ( edx != i ) )
        mov al,' '
        stosb
    .endif
    mov byte ptr [edi],NULLC

    ;
    ; RET without argument? Then calculate the value
    ;
    .if ( is_iret == FALSE && edx == i )
        .if ( ModuleInfo.epiloguemode != PEM_NONE )
            movzx eax,[ecx].asym.langtype
            .switch( eax )
            .case LANG_BASIC
            .case LANG_FORTRAN
            .case LANG_PASCAL
                .if ( [esi].parasize != 0 )
                    xor eax,eax
                    .if ( ModuleInfo.radix != 10 )
                        mov al,'t'
                    .endif
                    tsprintf( edi, "%d%c", [esi].parasize, eax )
                .endif
                .endc
            .case LANG_SYSCALL
                .endc .if ( ModuleInfo.Ofssize != USE64 )
            .case LANG_FASTCALL
            .case LANG_VECTORCALL
                dec GetFastcallId(eax)
                imul ecx,eax,fastcall_conv
                fastcall_tab[ecx].handlereturn( CurrProc, &buffer )
                .endc
            .case LANG_STDCALL
                .if ( !( [esi].flags & PROC_HAS_VARARG ) && [esi].parasize )
                    xor eax,eax
                    .if ( ModuleInfo.radix != 10 )
                        mov al,'t'
                    .endif
                    tsprintf( edi, "%d%c", [esi].parasize, eax )
                .endif
                .endc
            .endsw
        .endif
    .else
        ;
        ; v2.04: changed. Now works for both RET nn and IRETx
        ; v2.06: changed. Now works even if RET has ben "renamed"
        ;
        strcpy( edi, [ebx].tokpos )
    .endif
    AddLineQueue( &buffer )
    RunLineQueue()
   .return( NOT_ERROR )

RetInstr endp

;
; init this module. called for every pass.
;

ProcInit proc

    mov ProcStack,NULL
    mov CurrProc ,NULL
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
