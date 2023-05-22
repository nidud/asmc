; EXTERN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Processing of directives
;               PUBLIC
;               EXT[E]RN
;               EXTERNDEF
;               PROTO
;               COMM
;

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include fastpass.inc
include listing.inc
include equate.inc
include fixup.inc
include mangle.inc
include label.inc
include input.inc
include expreval.inc
include types.inc
include condasm.inc
include proc.inc
include extern.inc

; Masm accepts EXTERN for internal absolute symbols:
; X EQU 0
; EXTERN X:ABS
;
; However, the other way:
; EXTERN X:ABS
; X EQU 0
;
; is rejected! MASM_EXTCOND=1 will copy this behavior for JWasm.

define MASM_EXTCOND 1 ; 1 is Masm compatible

szCOMM equ <"COMM">

define mangle_type NULL

    .code

; create external.
; sym must be NULL or of state SYM_UNDEFINED!

CreateExternal proc fastcall private uses rsi sym:ptr asym, name:string_t, weak:char_t

    mov rsi,rcx
    .if ( rsi == NULL )
        mov rsi,SymCreate( rdx )
    .else
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rsi )
    .endif

    .if ( rsi )
        mov [rsi].asym.state,SYM_EXTERNAL
        mov [rsi].asym.segoffsize,ModuleInfo.Ofssize
        and [rsi].asym.sflags,not ( S_WEAK or S_ISCOM )
        .if ( weak )
            or [rsi].asym.sflags,S_WEAK
        .endif
        sym_add_table( &SymTables[TAB_EXT*symbol_queue], rsi ) ; add EXTERNAL
    .endif
    .return( rsi )

CreateExternal endp


; create communal.
; sym must be NULL or of state SYM_UNDEFINED!

CreateComm proc fastcall private uses rsi sym:ptr asym, name:string_t

    mov rsi,rcx
    .if ( rsi == NULL )
        mov rsi,SymCreate( rdx )
    .else
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rsi )
    .endif

    .if ( rsi )
        mov [rsi].asym.state,SYM_EXTERNAL
        mov [rsi].asym.segoffsize,ModuleInfo.Ofssize
        mov [rsi].asym.is_far,0
        and [rsi].asym.sflags,not S_WEAK
        or  [rsi].asym.sflags,S_ISCOM
        sym_add_table( &SymTables[TAB_EXT*symbol_queue], rsi ) ; add EXTERNAL
    .endif
    .return( rsi )

CreateComm endp


; create a prototype.
; used by PROTO, EXTERNDEF and EXT[E]RN directives.

    assume rbx:ptr asm_tok

CreateProto proc __ccall private uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok, name:string_t, langtype:byte

    mov rsi,SymSearch(name)

    ; the symbol must be either NULL or state
    ; - SYM_UNDEFINED
    ; - SYM_EXTERNAL + isproc == FALSE ( previous EXTERNDEF )
    ; - SYM_EXTERNAL + isproc == TRUE ( previous PROTO )
    ; - SYM_INTERNAL + isproc == TRUE ( previous PROC )

    .if ( rsi == NULL || [rsi].asym.state == SYM_UNDEFINED ||
          ( [rsi].asym.state == SYM_EXTERNAL && ( [rsi].asym.sflags & S_WEAK ) &&
            !( [rsi].asym.flags & S_ISPROC ) ) )

        .if ( CreateProc( rsi, name, SYM_EXTERNAL ) == NULL )
            .return ; name was probably invalid
        .endif
        mov rsi,rax

    .elseif ( !( [rsi].asym.flags & S_ISPROC ) )
        asmerr( 2005, [rsi].asym.name )
        .return( NULL )
    .endif

    imul ebx,i,asm_tok
    add rbx,tokenarray

    .if ( [rbx].token == T_ID )

        mov rdi,[rbx].string_ptr
        mov eax,[rdi]
        or  al,0x20
        .if ( ax == 'c' )

            mov [rbx].token,T_RES_ID
            mov [rbx].tokval,T_CCALL
            mov [rbx].bytval,1
        .endif
    .endif

    ; a PROTO typedef may be used

    .if ( [rbx].token == T_ID )

        mov rdi,SymSearch( [rbx].string_ptr )
        .if ( rax && [rax].asym.state == SYM_TYPE && [rax].asym.mem_type == MT_PROC )
            inc i
            add rbx,asm_tok
            .if ( [rbx].token != T_FINAL )
                asmerr( 2008, [rbx].string_ptr )
               .return( NULL )
            .endif
            CopyPrototype( rsi, [rdi].asym.target_type )
           .return( rsi )
        .endif
    .endif

    .if ( Parse_Pass == PASS_1 )
        .ifd ( ParseProc( rsi, i, tokenarray, FALSE, langtype ) == ERROR )
            .return( NULL )
        .endif
        mov [rsi].asym.dll,ModuleInfo.CurrDll
    .else
        or  [rsi].asym.flags,S_ISDEFINED
    .endif
    .return( rsi )

CreateProto endp


; externdef [ attr ] symbol:type [, symbol:type,...]

ExterndefDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local token:string_t
  local langtype:byte
  local isnew:char_t
  local ti:qualified_type

    inc i ; skip EXTERNDEF token

    .repeat

        mov ti.Ofssize,ModuleInfo.Ofssize

        ; get the symbol language type if present

        mov langtype,ModuleInfo.langtype
        GetLangType( &i, tokenarray, &langtype )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        ; get the symbol name

        .if ( [rbx].token != T_ID )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif
        mov token,[rbx].string_ptr
        inc i
        add rbx,asm_tok

        ; go past the colon

        .if ( [rbx].token != T_COLON )
            .return( asmerr( 2065, "colon" ) )
        .endif
        inc i
        add rbx,asm_tok
        mov rsi,SymSearch( token )

        mov ti.mem_type,MT_EMPTY
        mov ti.size,0
        mov ti.is_ptr,0
        mov ti.is_far,FALSE
        mov ti.ptr_memtype,MT_EMPTY
        mov ti.symtype,NULL
        mov ti.Ofssize,ModuleInfo.Ofssize

        mov rcx,[rbx].string_ptr
        mov eax,[rcx]
        or  eax,0x202020

        .if ( [rbx].token == T_ID && eax == 'sba' )

            inc i
            add rbx,asm_tok

        .elseif ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_PROTO )

            ; dont scan this line further!
            ; CreateProto() will either define a SYM_EXTERNAL or fail
            ; if there's a syntax error or symbol redefinition.

            mov ecx,i
            inc ecx
            .if CreateProto( ecx, tokenarray, token, langtype )
                .return( NOT_ERROR )
            .endif
            .return( ERROR )

        .elseif ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )

            .return .ifd ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )

            imul ebx,i,asm_tok
            add rbx,tokenarray
        .endif

        mov isnew,FALSE
        .if ( rsi == NULL || [rsi].asym.state == SYM_UNDEFINED )

            mov rsi,CreateExternal( rsi, token, TRUE )
            mov isnew,TRUE
        .endif

        ; new symbol?

        mov rdi,ti.symtype

        .if ( isnew )

            ; v2.05: added to accept type prototypes

            .if ( ti.is_ptr == 0 && rdi && [rdi].asym.flags & S_ISPROC )

                CreateProc( rsi, NULL, SYM_EXTERNAL )
                CopyPrototype( rsi, rdi )
                mov ti.mem_type,[rdi].asym.mem_type
                mov ti.symtype,NULL
            .endif

            .switch ( ti.mem_type )

            .case MT_EMPTY
                .endc
            .case MT_FAR

                ; v2.04: don't inherit current segment for FAR externals
                ; if -Zg is set.

                .endc .if ( Options.masm_compat_gencode )

                ; fall through

            .default

                mov [rsi].asym.segm,CurrSeg
            .endsw

            mov [rsi].asym.Ofssize,ti.Ofssize
            mov al,ti.Ofssize

            .if ( ti.is_ptr == 0 && al != ModuleInfo.Ofssize )

                mov [rsi].asym.segoffsize,al
                mov rcx,[rsi].asym.segm
                .if ( rcx )
                    mov rdx,[rcx].dsym.seginfo
                    .if ( [rdx].seg_info.Ofssize != al )
                        mov [rsi].asym.segm,NULL
                    .endif
                .endif
            .endif

            mov [rsi].asym.mem_type,ti.mem_type
            mov [rsi].asym.is_ptr,ti.is_ptr
            mov [rsi].asym.is_far,ti.is_far
            mov [rsi].asym.ptr_memtype,ti.ptr_memtype
            mov rax,ti.symtype
            .if ( ti.mem_type == MT_TYPE )
                mov [rsi].asym.type,rax
            .else
                mov [rsi].asym.target_type,rax
            .endif

            ; v2.04: only set language if there was no previous definition

            SetMangler( rsi, langtype, mangle_type )

        .elseif ( Parse_Pass == PASS_1 )

            ; v2.05: added to accept type prototypes

            .if ( ti.is_ptr == 0 && rdi && [rdi].asym.flags & S_ISPROC )

                mov ti.mem_type,[rdi].asym.mem_type
                mov ti.symtype,NULL
            .endif

            ; ensure that the type of the symbol won't change

            .if ( [rsi].asym.mem_type != ti.mem_type )

                ; if the symbol is already defined (as SYM_INTERNAL), Masm
                ; won't display an error. The other way, first externdef and
                ; then the definition, will make Masm complain, however

                asmerr( 8004, [rsi].asym.name )

            .elseif ( [rsi].asym.mem_type == MT_TYPE && [rsi].asym.type != ti.symtype )

                mov rcx,rsi

                ; skip alias types and compare the base types

                .while ( [rcx].asym.type )
                    mov rcx,[rcx].asym.type
                .endw
                .while ( [rdi].asym.type )
                    mov rdi,[rdi].asym.type
                .endw
                .if ( rcx != rdi )
                    asmerr( 8004, [rsi].asym.name )
                .endif
            .endif

            ; v2.04: emit a - weak - warning if language differs.
            ; Masm doesn't warn.

            .if ( langtype != LANG_NONE && [rsi].asym.langtype != langtype )
                asmerr( 7000, [rsi].asym.name )
            .endif
        .endif
        or [rsi].asym.flags,S_ISDEFINED

        .if ( [rsi].asym.state == SYM_INTERNAL && !( [rsi].asym.flags & S_ISPUBLIC ) )
            or [rsi].asym.flags,S_ISPUBLIC
            AddPublicData(rsi)
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
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif
        .endif
    .until ( i >= Token_Count )

    .return( NOT_ERROR )

ExterndefDirective endp


; PROTO directive.
; <name> PROTO <params> is semantically identical to:
; EXTERNDEF <name>: PROTO <params>

ProtoDirective proc __ccall uses rbx i:int_t, tokenarray:ptr asm_tok

    ldr rbx,tokenarray
    .if ( Parse_Pass != PASS_1 )

        ; v2.04: set the "defined" flag

        .if ( SymSearch( [rbx].string_ptr ) )
            .if ( [rax].asym.flags & S_ISPROC )
                or [rax].asym.flags,S_ISDEFINED
            .endif
        .endif
        .return( NOT_ERROR )
    .endif
    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [rbx+rcx].string_ptr ) )
    .endif
    .if CreateProto( 2, tokenarray, [rbx].string_ptr, ModuleInfo.langtype )
        mov eax,NOT_ERROR
    .else
        mov eax,ERROR
    .endif
    ret

ProtoDirective endp


; helper for EXTERN directive.
; also used to create 16-bit floating-point fixups.
; sym must be NULL or of state SYM_UNDEFINED!

MakeExtern proc __ccall name:string_t, mem_type:byte, vartype:ptr asym, sym:ptr asym, Ofssize:byte

    mov rcx,CreateExternal( sym, name, FALSE )
    .return .if !rax
    .if ( mem_type == MT_EMPTY )
    .elseif ( Options.masm_compat_gencode == FALSE || mem_type != MT_FAR )
        mov [rcx].asym.segm,CurrSeg
    .endif
    or  [rcx].asym.flags,S_ISDEFINED
    mov [rcx].asym.mem_type,mem_type
    mov [rcx].asym.segoffsize,Ofssize
    mov [rcx].asym.type,vartype
   .return( rcx )

MakeExtern endp


; handle optional alternate names in EXTERN directive

HandleAltname proc __ccall private uses rsi rdi rbx altname:string_t, sym:ptr asym

    mov rsi,sym

    .if ( altname && [rsi].asym.state == SYM_EXTERNAL )

        mov rdi,SymSearch( altname )

        ; altname symbol changed?

        .if ( [rsi].asym.altname && [rsi].asym.altname != rdi )
            .return( asmerr( 2005, [rsi].asym.name ) )
        .endif

        .if ( Parse_Pass > PASS_1 )
            .if ( [rdi].asym.state == SYM_UNDEFINED )
                asmerr( 2006, altname )
            .elseif ( [rdi].asym.state != SYM_INTERNAL && [rdi].asym.state != SYM_EXTERNAL )
                asmerr( 2004, altname )
            .else
                .if ( [rdi].asym.state == SYM_INTERNAL && !( [rdi].asym.flags & S_ISPUBLIC ) )
                    .if ( Options.output_format == OFORMAT_COFF ||
                          Options.output_format == OFORMAT_ELF )
                        asmerr( 2217, altname )
                    .endif
                .endif
                .if ( [rsi].asym.mem_type != [rdi].asym.mem_type )
                    asmerr( 2004, altname )
                .endif
            .endif
        .else

            .if ( rdi )
                .if ( [rdi].asym.state != SYM_INTERNAL &&
                      [rdi].asym.state != SYM_EXTERNAL &&
                      [rdi].asym.state != SYM_UNDEFINED )
                    .return( asmerr( 2004, altname ) )
                .endif
            .else
                mov rdi,SymCreate( altname )
                sym_add_table( &SymTables[TAB_UNDEF*symbol_queue], rdi )
            .endif

            ; make sure the alt symbol becomes strong if it is an external
            ; v2.11: don't do this for OMF ( maybe neither for COFF/ELF? )

            .if ( Options.output_format != OFORMAT_OMF )
                or [rdi].asym.flags,S_USED
            .endif

            ; symbol inserted in the "weak external" queue?
            ; currently needed for OMF only.

            .if ( [rsi].asym.altname == NULL )
                mov [rsi].asym.altname,rdi
            .endif
        .endif
    .endif
    .return( NOT_ERROR )

HandleAltname endp


; syntax: EXT[E]RN [lang_type] name (altname) :type [, ...]

ExternDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local langtype:byte
  local ti:qualified_type
  local altname:string_t
  local token:string_t


    inc i ; skip EXT[E]RN token

    .repeat

        mov altname,NULL

        ; get the symbol language type if present

        mov langtype,ModuleInfo.langtype
        GetLangType( &i, tokenarray, &langtype )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        ; get the symbol name

        .if ( [rbx].token != T_ID )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif
        mov token,[rbx].string_ptr
        inc i
        add rbx,asm_tok

        ; go past the optional alternative name (weak ext, default resolution)

        .if ( [rbx].token == T_OP_BRACKET )

            inc i
            add rbx,asm_tok

            .if ( [rbx].token != T_ID )
                .return( asmerr( 2008, [rbx].string_ptr ) )
            .endif
            mov altname,[rbx].string_ptr
            inc i
            add rbx,asm_tok
            .if ( [rbx].token != T_CL_BRACKET )
                .return( asmerr( 2065, ")" ) )
            .endif
            inc i
            add rbx,asm_tok
        .endif

        ; go past the colon

        .if ( [rbx].token != T_COLON )
            .return( asmerr( 2065, ":" ) )
        .endif

        inc i
        add rbx,asm_tok
        mov rdi,SymSearch( token )

        mov ti.mem_type,MT_EMPTY
        mov ti.size,0
        mov ti.is_ptr,0
        mov ti.is_far,FALSE
        mov ti.ptr_memtype,MT_EMPTY
        mov ti.symtype,NULL
        mov ti.Ofssize,ModuleInfo.Ofssize

        xor eax,eax
        .if ( [rbx].token == T_ID )
            mov rcx,[rbx].string_ptr
            mov eax,[rcx]
            or  eax,0x202020
        .endif

        .if ( eax == 'sba' )

            inc i

        .elseif ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_PROTO )

            ; dont scan this line further
            ; CreateProto() will define a SYM_EXTERNAL

            mov ecx,i
            inc ecx
            mov rdi,CreateProto( ecx, tokenarray, token, langtype )
            .if ( rdi == NULL )
                .return( ERROR )
            .endif
            .if ( [rdi].asym.state == SYM_EXTERNAL )
                and [rdi].asym.sflags,not S_WEAK
                .return( HandleAltname( altname, rdi ) )
            .else

                ; unlike EXTERNDEF, EXTERN doesn't allow a PROC for the same name

                .return( asmerr( 2005, [rdi].asym.name ) )
            .endif
        .elseif ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )
            .ifd ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                .return( ERROR )
            .endif
        .endif

        .if ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )

            xor ecx,ecx
            .if ( ti.mem_type == MT_TYPE )
                mov rcx,ti.symtype
            .endif
            movzx edx,ti.Ofssize
            .if ( ti.is_ptr )
                mov dl,ModuleInfo.Ofssize
            .endif

            .if ( MakeExtern( token, ti.mem_type, rcx, rdi, dl ) == NULL )
                .return( ERROR )
            .endif
            mov rdi,rax

            ; v2.05: added to accept type prototypes

            mov rsi,ti.symtype

            .if ( ti.is_ptr == 0 && rsi && [rsi].asym.flags & S_ISPROC )

                CreateProc( rdi, NULL, SYM_EXTERNAL )

                ; v2.09: reset the weak bit that has been set inside CreateProc()

                and [rdi].asym.sflags,not S_WEAK

                CopyPrototype( rdi, rsi )
                mov ti.mem_type,[rsi].asym.mem_type
                mov ti.symtype,NULL
            .endif

        .else

if MASM_EXTCOND

            ; allow internal AND external definitions for equates

            .if ( [rdi].asym.state == SYM_INTERNAL && [rdi].asym.mem_type == MT_EMPTY )
            .else
endif
                .if ( [rdi].asym.state != SYM_EXTERNAL )
                    .return( asmerr( 2005, token ) )
                .endif
if MASM_EXTCOND
            .endif
endif
            ; v2.05: added to accept type prototypes

            mov rsi,ti.symtype
            .if ( ti.is_ptr == 0 && rsi && [rsi].asym.flags & S_ISPROC )

                mov ti.mem_type,[rsi].asym.mem_type
                mov ti.symtype,NULL
            .endif
            mov rdx,[rdi].asym.target_type
            .if ( [rdi].asym.mem_type == MT_TYPE )
                mov rdx,[rdi].asym.type
            .endif

            .if ( [rdi].asym.mem_type != ti.mem_type ||
                  [rdi].asym.is_ptr != ti.is_ptr ||
                  [rdi].asym.is_far != ti.is_far ||
                  ( [rdi].asym.is_ptr && [rdi].asym.ptr_memtype != ti.ptr_memtype ) ||
                  rdx != ti.symtype ||
                  ( langtype != LANG_NONE && [rdi].asym.langtype != LANG_NONE && [rdi].asym.langtype != langtype ) )

                .return( asmerr( 2004, token ) )
            .endif
        .endif

        or  [rdi].asym.flags,S_ISDEFINED
        mov [rdi].asym.Ofssize,ti.Ofssize

        .if ( ti.is_ptr == 0 && ti.Ofssize != ModuleInfo.Ofssize )
            mov rcx,[rdi].asym.segm
            .if ( rcx )
                mov rdx,[rcx].dsym.seginfo
            .endif
            mov [rdi].asym.segoffsize,ti.Ofssize
            .if ( rcx && [rdx].seg_info.Ofssize != al )
                mov [rdi].asym.segm,NULL
            .endif
        .endif

        mov [rdi].asym.mem_type,ti.mem_type
        mov [rdi].asym.is_ptr,ti.is_ptr
        mov [rdi].asym.is_far,ti.is_far
        mov [rdi].asym.ptr_memtype,ti.ptr_memtype
        .if ( ti.mem_type == MT_TYPE )
            mov [rdi].asym.type,ti.symtype
        .else
            mov [rdi].asym.target_type,ti.symtype
        .endif

        HandleAltname( altname, rdi )
        SetMangler( rdi, langtype, mangle_type )

        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if ( [rbx].token != T_FINAL )
            mov ecx,i
            inc ecx
            .if ( [rbx].token == T_COMMA &&  ( ecx < Token_Count ) )
                inc i
            .else
                .return( asmerr( 2008, [rbx].string_ptr ) )
            .endif
        .endif

     .until ( i >= Token_Count )

    .return( NOT_ERROR )

ExternDirective endp


; helper for COMM directive

MakeComm proc __ccall private uses rdi name:string_t, sym:ptr asym, size:dword, count:dword, isfar:uchar_t

    mov rdi,CreateComm( sym, name )
    .return .if ( rdi == NULL )

    mov [rdi].asym.total_length,count
    mov [rdi].asym.is_far,isfar

    ; v2.04: don't set segment if communal is far and -Zg is set

    .if ( Options.masm_compat_gencode == FALSE || isfar == FALSE )
        mov [rdi].asym.segm,CurrSeg
    .endif

    MemtypeFromSize( size, &[rdi].asym.mem_type )

    ; v2.04: warning added ( Masm emits an error )
    ; v2.05: code active for 16-bit only

    .if ( ModuleInfo.Ofssize == USE16 )
        mov eax,size
        mul count
        .if ( eax > 0x10000 )
            asmerr( 8003, [rdi].asym.name )
        .endif
    .endif
    mov eax,size
    mul count
    mov [rdi].asym.total_size,eax
    .return( rdi )

MakeComm endp


; define "communal" items
; syntax:
; COMM [langtype] [NEAR|FAR] label:type[:count] [, ... ]
; the size & count values must NOT be forward references!

CommDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local token:string_t
  local isfar:byte
  local tmp:int_t
  local size:uint_32  ; v2.12: changed from 'int' to 'uint_32'
  local count:uint_32 ; v2.12: changed from 'int' to 'uint_32'
  local sym:ptr asym
  local opndx:expr
  local langtype:byte

    inc i ; skip COMM token

    .for ( : i < Token_Count: i++ )

        ; get the symbol language type if present

        mov langtype,ModuleInfo.langtype
        GetLangType( &i, tokenarray, &langtype )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        ; get the -optional- distance ( near or far )

        mov isfar,FALSE

        .if ( [rbx].token == T_STYPE )

            .switch ( [rbx].tokval )

            .case T_FAR
            .case T_FAR16
            .case T_FAR32

                .if ( ModuleInfo._model == MODEL_FLAT )
                    asmerr( 2178 )
                .else
                    mov isfar,TRUE
                .endif

                ; no break

            .case T_NEAR
            .case T_NEAR16
            .case T_NEAR32
                inc i
                add rbx,asm_tok
            .endsw
        .endif

        ; v2.08: ensure token is a valid id

        .if ( [rbx].token != T_ID )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif

        ; get the symbol name

        mov token,[rbx].string_ptr
        inc i
        add rbx,asm_tok

        ; go past the colon

        .if ( [rbx].token != T_COLON )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif
        inc i
        add rbx,asm_tok

        ; the evaluator cannot handle a ':' so scan for one first

        .for ( ecx = i, rdx = rbx: ecx < Token_Count: ecx++, rdx += asm_tok )
            .break .if ( [rdx].asm_tok.token == T_COLON )
        .endf

        ; v2.10: expression evaluator isn't to accept forward references

        .ifd ( EvalOperand( &i, tokenarray, ecx, &opndx, EXPF_NOUNDEF ) == ERROR )
            .return( ERROR )
        .endif

        ; v2.03: a string constant is accepted by Masm
        ; v2.11: don't accept NEAR or FAR
        ; v2.12: check for too large value added

        mov al,opndx.mem_type
        and al,MT_SPECIAL_MASK
        .if ( opndx.kind != EXPR_CONST )
            asmerr( 2026 )
        .elseif ( al == MT_ADDRESS )
            asmerr( 2104, token )
        .elseif ( opndx.hvalue != 0 && opndx.hvalue != -1 )
            EmitConstError( &opndx )
        .elseif ( opndx.uvalue == 0 )
            asmerr( 2090 )
        .endif

        mov size,opndx.uvalue
        mov count,1

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( [rbx].token == T_COLON )

            inc i

            ; get optional count argument
            ; v2.10: expression evaluator isn't to accept forward references

            .ifd ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
                .return( ERROR )
            .endif

            ; v2.03: a string constant is acceptable!
            ; v2.12: check for too large value added

            .if ( opndx.kind != EXPR_CONST )
                asmerr( 2026 )
            .elseif ( opndx.hvalue != 0 && opndx.hvalue != -1 )
                EmitConstError( &opndx )
            .elseif ( opndx.uvalue == 0 )
                asmerr( 2090 )
            .endif

            mov count,opndx.uvalue
        .endif

        mov rdi,SymSearch( token )
        .if ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )
            mov rdi,MakeComm( token, rdi, size, count, isfar )
            .if ( rdi == NULL )
                .return( ERROR )
            .endif
        .elseif ( [rdi].asym.state != SYM_EXTERNAL || !( [rdi].asym.sflags & S_ISCOM ) )
            .return( asmerr( 2005, [rdi].asym.name ) )
        .else
            mov eax,[rdi].asym.total_size
            cdq
            div [rdi].asym.total_length
            mov ecx,count
            .if ( ecx != [rdi].asym.total_length || size != eax )
                .return( asmerr( 2007, szCOMM, [rdi].asym.name ) )
            .endif
        .endif
        or [rdi].asym.flags,S_ISDEFINED
        SetMangler( rdi, langtype, mangle_type )

        imul ebx,i,asm_tok
        add rbx,tokenarray
        .if ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )
            .return( asmerr( 2008, [rbx].tokpos ) )
        .endif
    .endf
    .return( NOT_ERROR )

CommDirective endp


; syntax: PUBLIC [lang_type] name [, ...]

PublicDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local token:string_t
  local sym:ptr asym
  local skipitem:sbyte
  local langtype:byte

    inc i ; skip PUBLIC directive

    .repeat

        ; read the optional language type

        mov langtype,ModuleInfo.langtype
        GetLangType( &i, tokenarray, &langtype )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( [rbx].token != T_ID )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif

        ; get the symbol name

        mov token,[rbx].string_ptr
        inc i
        add rbx,asm_tok

        ; Add the public name

        mov rdi,SymSearch( token )
        .if ( Parse_Pass == PASS_1 )
            .if ( rdi == NULL )
                .if ( SymCreate( token ) )
                    mov rdi,rax
                    sym_add_table( &SymTables[TAB_UNDEF*symbol_queue], rdi )
                .else
                    .return( ERROR ) ; name was too long
                .endif
            .endif
            mov skipitem,FALSE
        .else
            .if ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )
                asmerr( 2006, token )
            .endif
        .endif
        .if ( rdi )
            .switch ( [rdi].asym.state )
            .case SYM_UNDEFINED
                .endc
            .case SYM_INTERNAL
                .if ( [rdi].asym.flags & S_SCOPED )
                    asmerr( 2014, [rdi].asym.name )
                    mov skipitem,TRUE
                .endif
                .endc
            .case SYM_EXTERNAL
                .if ( [rdi].asym.sflags & S_ISCOM )
                    asmerr( 2014, [rdi].asym.name )
                    mov skipitem,TRUE
                .elseif ( !( [rdi].asym.sflags & S_WEAK ) )
                    ; for EXTERNs, emit a different error msg
                    asmerr( 2005, [rdi].asym.name )
                    mov skipitem,TRUE
                .endif
                .endc
            .default
                asmerr( 2014, [rdi].asym.name )
                mov skipitem,TRUE
            .endsw
            .if ( Parse_Pass == PASS_1 && skipitem == FALSE )
                .if ( !( [rdi].asym.flags & S_ISPUBLIC ) )
                    or [rdi].asym.flags,S_ISPUBLIC
                    AddPublicData( rdi ) ; put it into the public table
                .endif
                SetMangler( rdi, langtype, mangle_type )
            .endif
        .endif

        .if ( [rbx].token != T_FINAL )
            .if ( [rbx].token == T_COMMA )
                mov ecx,i
                inc ecx
                .if ( ecx < Token_Count )
                    inc i
                .endif
            .else
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif
        .endif

    .until ( i >= Token_Count )
    .return( NOT_ERROR )

PublicDirective endp

    end
