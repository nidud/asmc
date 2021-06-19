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

CreateExternal proc private uses esi sym:ptr asym, name:string_t, weak:char_t

    mov esi,sym
    .if ( esi == NULL )
        mov esi,SymCreate( name )
    .else
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], esi )
    .endif

    .if ( esi )
        mov [esi].asym.state,SYM_EXTERNAL
        mov al,ModuleInfo.Ofssize
        .if ( weak )
            or  al,S_WEAK
        .endif
        and [esi].asym.sflags,not ( S_SEGOFSSIZE or S_ISCOM )
        or  [esi].asym.sflags,al
        sym_add_table( &SymTables[TAB_EXT*symbol_queue], esi ) ; add EXTERNAL
    .endif
    .return( esi )

CreateExternal endp

; create communal.
; sym must be NULL or of state SYM_UNDEFINED!

CreateComm proc private uses esi sym:ptr asym, name:string_t

    mov esi,sym
    .if ( esi == NULL )
        mov esi,SymCreate( name )
    .else
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], esi )
    .endif

    .if ( esi )
        mov [esi].asym.state,SYM_EXTERNAL
        mov al,ModuleInfo.Ofssize
        or  al,S_ISCOM
        and [esi].asym.sflags,not ( S_SEGOFSSIZE or S_WEAK or S_ISFAR )
        or  [esi].asym.sflags,al
        sym_add_table( &SymTables[TAB_EXT*symbol_queue], esi ) ; add EXTERNAL
    .endif
    .return( esi )

CreateComm endp

; create a prototype.
; used by PROTO, EXTERNDEF and EXT[E]RN directives.

    assume ebx:ptr asm_tok

CreateProto proc private uses esi edi ebx i:int_t, tokenarray:ptr asm_tok, name:string_t, langtype:byte

    mov esi,SymSearch( name )

    ; the symbol must be either NULL or state
    ; - SYM_UNDEFINED
    ; - SYM_EXTERNAL + isproc == FALSE ( previous EXTERNDEF )
    ; - SYM_EXTERNAL + isproc == TRUE ( previous PROTO )
    ; - SYM_INTERNAL + isproc == TRUE ( previous PROC )

    .if ( esi == NULL || [esi].asym.state == SYM_UNDEFINED || \
          ( [esi].asym.state == SYM_EXTERNAL && ( [esi].asym.sflags & S_WEAK ) && \
            !( [esi].asym.flag1 & S_ISPROC ) ) )

        .if ( CreateProc( esi, name, SYM_EXTERNAL ) == NULL )
            .return ; name was probably invalid
        .endif
        mov esi,eax

    .elseif ( !( [esi].asym.flag1 & S_ISPROC ) )
        asmerr( 2005, [esi].asym.name )
        .return( NULL )
    .endif

    imul ebx,i,asm_tok
    add ebx,tokenarray

    .if ( [ebx].token == T_ID )

        mov edi,[ebx].string_ptr
        mov eax,[edi]
        or  al,0x20
        .if ( ax == 'c' )

            mov [ebx].token,T_RES_ID
            mov [ebx].tokval,T_CCALL
            mov [ebx].bytval,1
        .endif
    .endif

    ; a PROTO typedef may be used

    .if ( [ebx].token == T_ID )

        mov edi,SymSearch( [ebx].string_ptr )
        .if ( eax && [eax].asym.state == SYM_TYPE && [eax].asym.mem_type == MT_PROC )
            inc i
            add ebx,asm_tok
            .if ( [ebx].token != T_FINAL )
                asmerr( 2008, [ebx].string_ptr )
                .return( NULL )
            .endif
            CopyPrototype( esi, [edi].asym.target_type )
            .return( esi )
        .endif
    .endif

    .if ( Parse_Pass == PASS_1 )
        .if ( ParseProc( esi, i, tokenarray, FALSE, langtype ) == ERROR )
            .return( NULL )
        .endif
        mov [esi].asym.dll,ModuleInfo.CurrDll
    .else
        or  [esi].asym.flags,S_ISDEFINED
    .endif
    .return( esi )

CreateProto endp

; externdef [ attr ] symbol:type [, symbol:type,...]

ExterndefDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

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
        add ebx,tokenarray

        ; get the symbol name

        .if ( [ebx].token != T_ID )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        mov token,[ebx].string_ptr
        inc i
        add ebx,asm_tok

        ; go past the colon

        .if ( [ebx].token != T_COLON )
            .return( asmerr( 2065, "colon" ) )
        .endif
        inc i
        add ebx,asm_tok
        mov esi,SymSearch( token )

        mov ti.mem_type,MT_EMPTY
        mov ti.size,0
        mov ti.is_ptr,0
        mov ti.is_far,FALSE
        mov ti.ptr_memtype,MT_EMPTY
        mov ti.symtype,NULL
        mov ti.Ofssize,ModuleInfo.Ofssize

        mov ecx,[ebx].string_ptr
        mov eax,[ecx]
        or  eax,0x202020

        .if ( [ebx].token == T_ID && eax == 'sba' )

            inc i
            add ebx,asm_tok

        .elseif ( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_PROTO )

            ; dont scan this line further!
            ; CreateProto() will either define a SYM_EXTERNAL or fail
            ; if there's a syntax error or symbol redefinition.

            mov ecx,i
            inc ecx
            .if CreateProto( ecx, tokenarray, token, langtype )
                .return( NOT_ERROR )
            .endif
            .return( ERROR )

        .elseif ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )

            .return .if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )

            imul ebx,i,asm_tok
            add ebx,tokenarray
        .endif

        mov isnew,FALSE
        .if ( esi == NULL || [esi].asym.state == SYM_UNDEFINED )

            mov esi,CreateExternal( esi, token, TRUE )
            mov isnew,TRUE
        .endif

        ; new symbol?

        mov edi,ti.symtype

        .if ( isnew )

            ; v2.05: added to accept type prototypes

            .if ( ti.is_ptr == 0 && edi && [edi].asym.flag1 & S_ISPROC )

                CreateProc( esi, NULL, SYM_EXTERNAL )
                CopyPrototype( esi, edi )
                mov ti.mem_type,[edi].asym.mem_type
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

                mov [esi].asym.segm,CurrSeg
            .endsw

            mov [esi].asym.Ofssize,ti.Ofssize
            mov al,ti.Ofssize

            .if ( ti.is_ptr == 0 && al != ModuleInfo.Ofssize )

                and [esi].asym.sflags,not S_SEGOFSSIZE
                or  [esi].asym.sflags,al
                mov ecx,[esi].asym.segm
                .if ( ecx )
                    mov edx,[ecx].dsym.seginfo
                    .if ( [edx].seg_info.Ofssize != al )
                        mov [esi].asym.segm,NULL
                    .endif
                .endif
            .endif

            mov [esi].asym.mem_type,ti.mem_type
            mov [esi].asym.is_ptr,ti.is_ptr
            and [esi].asym.sflags,not S_ISFAR
            .if ( ti.is_far )
                or [esi].asym.sflags,S_ISFAR
            .endif
            mov [esi].asym.ptr_memtype,ti.ptr_memtype
            mov eax,ti.symtype
            .if ( ti.mem_type == MT_TYPE )
                mov [esi].asym.type,eax
            .else
                mov [esi].asym.target_type,eax
            .endif

            ; v2.04: only set language if there was no previous definition

            SetMangler( esi, langtype, mangle_type )

        .elseif ( Parse_Pass == PASS_1 )

            ; v2.05: added to accept type prototypes

            .if ( ti.is_ptr == 0 && edi && [edi].asym.flag1 & S_ISPROC )

                mov ti.mem_type,[edi].asym.mem_type
                mov ti.symtype,NULL
            .endif

            ; ensure that the type of the symbol won't change

            .if ( [esi].asym.mem_type != ti.mem_type )

                ; if the symbol is already defined (as SYM_INTERNAL), Masm
                ; won't display an error. The other way, first externdef and
                ; then the definition, will make Masm complain, however

                asmerr( 8004, [esi].asym.name )

            .elseif ( [esi].asym.mem_type == MT_TYPE && [esi].asym.type != ti.symtype )

                mov ecx,esi

                ; skip alias types and compare the base types

                .while ( [ecx].asym.type )
                    mov ecx,[ecx].asym.type
                .endw
                .while ( [edi].asym.type )
                    mov edi,[edi].asym.type
                .endw
                .if ( ecx != edi )
                    asmerr( 8004, [esi].asym.name )
                .endif
            .endif

            ; v2.04: emit a - weak - warning if language differs.
            ; Masm doesn't warn.

            .if ( langtype != LANG_NONE && [esi].asym.langtype != langtype )
                asmerr( 7000, [esi].asym.name )
            .endif
        .endif
        or [esi].asym.flags,S_ISDEFINED

        .if ( [esi].asym.state == SYM_INTERNAL && !( [esi].asym.flags & S_ISPUBLIC ) )
            or [esi].asym.flags,S_ISPUBLIC
            AddPublicData( esi )
        .endif

        .if ( [ebx].token != T_FINAL )
            .if ( [ebx].token == T_COMMA )
                mov eax,i
                inc eax
                .if ( eax < Token_Count )
                    inc i
                    add ebx,asm_tok
                .endif
            .else
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif
        .endif
    .until ( i >= Token_Count )

    .return( NOT_ERROR )

ExterndefDirective endp

; PROTO directive.
; <name> PROTO <params> is semantically identical to:
; EXTERNDEF <name>: PROTO <params>

ProtoDirective proc uses ebx i:int_t, tokenarray:ptr asm_tok

    mov ebx,tokenarray
    .if ( Parse_Pass != PASS_1 )

        ; v2.04: set the "defined" flag

        .if ( SymSearch( [ebx].string_ptr ) )
            .if ( [eax].asym.flags & S_ISPROC )
                or [eax].asym.flags,S_ISDEFINED
            .endif
        .endif
        .return( NOT_ERROR )
    .endif
    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [ebx+ecx].string_ptr ) )
    .endif
    .if CreateProto( 2, tokenarray, [ebx].string_ptr, ModuleInfo.langtype )
        mov eax,NOT_ERROR
    .else
        mov eax,ERROR
    .endif
    ret

ProtoDirective endp

; helper for EXTERN directive.
; also used to create 16-bit floating-point fixups.
; sym must be NULL or of state SYM_UNDEFINED!

MakeExtern proc name:string_t, mem_type:byte, vartype:ptr asym, sym:ptr asym, Ofssize:byte

    mov ecx,CreateExternal( sym, name, FALSE )
    .return .if !eax
    .if ( mem_type == MT_EMPTY )
    .elseif ( Options.masm_compat_gencode == FALSE || mem_type != MT_FAR )
        mov [ecx].asym.segm,CurrSeg
    .endif
    or  [ecx].asym.flags,S_ISDEFINED
    mov [ecx].asym.mem_type,mem_type
    and [ecx].asym.sflags,not S_SEGOFSSIZE
    or  [ecx].asym.sflags,Ofssize
    mov [ecx].asym.type,vartype
   .return( ecx )

MakeExtern endp

; handle optional alternate names in EXTERN directive

HandleAltname proc private uses esi edi ebx altname:string_t, sym:ptr asym

    mov esi,sym

    .if ( altname && [esi].asym.state == SYM_EXTERNAL )

        mov edi,SymSearch( altname )

        ; altname symbol changed?

        .if ( [esi].asym.altname && [esi].asym.altname != edi )
            .return( asmerr( 2005, [esi].asym.name ) )
        .endif

        .if ( Parse_Pass > PASS_1 )
            .if ( [edi].asym.state == SYM_UNDEFINED )
                asmerr( 2006, altname )
            .elseif ( [edi].asym.state != SYM_INTERNAL && [edi].asym.state != SYM_EXTERNAL )
                asmerr( 2004, altname )
            .else
                .if ( [edi].asym.state == SYM_INTERNAL && !( [edi].asym.flags & S_ISPUBLIC ) )
                    .if ( Options.output_format == OFORMAT_COFF || \
                          Options.output_format == OFORMAT_ELF )
                        asmerr( 2217, altname )
                    .endif
                .endif
                .if ( [esi].asym.mem_type != [edi].asym.mem_type )
                    asmerr( 2004, altname )
                .endif
            .endif
        .else

            .if ( edi )
                .if ( [edi].asym.state != SYM_INTERNAL && \
                      [edi].asym.state != SYM_EXTERNAL && \
                      [edi].asym.state != SYM_UNDEFINED )
                    .return( asmerr( 2004, altname ) )
                .endif
            .else
                mov edi,SymCreate( altname )
                sym_add_table( &SymTables[TAB_UNDEF*symbol_queue], edi )
            .endif

            ; make sure the alt symbol becomes strong if it is an external
            ; v2.11: don't do this for OMF ( maybe neither for COFF/ELF? )

            .if ( Options.output_format != OFORMAT_OMF )
                or [edi].asym.flags,S_USED
            .endif

            ; symbol inserted in the "weak external" queue?
            ; currently needed for OMF only.

            .if ( [esi].asym.altname == NULL )
                mov [esi].asym.altname,edi
            .endif
        .endif
    .endif
    .return( NOT_ERROR )

HandleAltname endp

; syntax: EXT[E]RN [lang_type] name (altname) :type [, ...]

ExternDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

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
        add ebx,tokenarray

        ; get the symbol name

        .if ( [ebx].token != T_ID )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        mov token,[ebx].string_ptr
        inc i
        add ebx,asm_tok

        ; go past the optional alternative name (weak ext, default resolution)

        .if ( [ebx].token == T_OP_BRACKET )

            inc i
            add ebx,asm_tok

            .if ( [ebx].token != T_ID )
                .return( asmerr( 2008, [ebx].string_ptr ) )
            .endif
            mov altname,[ebx].string_ptr
            inc i
            add ebx,asm_tok
            .if ( [ebx].token != T_CL_BRACKET )
                .return( asmerr( 2065, ")" ) )
            .endif
            inc i
            add ebx,asm_tok
        .endif

        ; go past the colon

        .if ( [ebx].token != T_COLON )
            .return( asmerr( 2065, ":" ) )
        .endif

        inc i
        add ebx,asm_tok
        mov edi,SymSearch( token )

        mov ti.mem_type,MT_EMPTY
        mov ti.size,0
        mov ti.is_ptr,0
        mov ti.is_far,FALSE
        mov ti.ptr_memtype,MT_EMPTY
        mov ti.symtype,NULL
        mov ti.Ofssize,ModuleInfo.Ofssize

        xor eax,eax
        .if ( [ebx].token == T_ID )
            mov ecx,[ebx].string_ptr
            mov eax,[ecx]
            or  eax,0x202020
        .endif

        .if ( eax == 'sba' )

            inc i

        .elseif ( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_PROTO )

            ; dont scan this line further
            ; CreateProto() will define a SYM_EXTERNAL

            mov ecx,i
            inc ecx
            mov edi,CreateProto( ecx, tokenarray, token, langtype )
            .if ( edi == NULL )
                .return( ERROR )
            .endif
            .if ( [edi].asym.state == SYM_EXTERNAL )
                and [edi].asym.sflags,not S_WEAK
                .return( HandleAltname( altname, edi ) )
            .else

                ; unlike EXTERNDEF, EXTERN doesn't allow a PROC for the same name

                .return( asmerr( 2005, [edi].asym.name ) )
            .endif
        .elseif ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )
            .if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                .return( ERROR )
            .endif
        .endif

        .if ( edi == NULL || [edi].asym.state == SYM_UNDEFINED )

            xor ecx,ecx
            .if ( ti.mem_type == MT_TYPE )
                mov ecx,ti.symtype
            .endif
            movzx edx,ti.Ofssize
            .if ( ti.is_ptr )
                mov dl,ModuleInfo.Ofssize
            .endif

            .if ( MakeExtern( token, ti.mem_type, ecx, edi, dl ) == NULL )
                .return( ERROR )
            .endif
            mov edi,eax

            ; v2.05: added to accept type prototypes

            mov esi,ti.symtype

            .if ( ti.is_ptr == 0 && esi && [esi].asym.flag1 & S_ISPROC )

                CreateProc( edi, NULL, SYM_EXTERNAL )

                ; v2.09: reset the weak bit that has been set inside CreateProc()

                and [edi].asym.sflags,not S_WEAK

                CopyPrototype( edi, esi )
                mov ti.mem_type,[esi].asym.mem_type
                mov ti.symtype,NULL
            .endif

        .else

if MASM_EXTCOND

            ; allow internal AND external definitions for equates

            .if ( [edi].asym.state == SYM_INTERNAL && [edi].asym.mem_type == MT_EMPTY )
            .else
endif
                .if ( [edi].asym.state != SYM_EXTERNAL )
                    .return( asmerr( 2005, token ) )
                .endif
if MASM_EXTCOND
            .endif
endif
            ; v2.05: added to accept type prototypes

            mov esi,ti.symtype
            .if ( ti.is_ptr == 0 && esi && [esi].asym.flag1 & S_ISPROC )

                mov ti.mem_type,[esi].asym.mem_type
                mov ti.symtype,NULL
            .endif
            mov edx,[edi].asym.target_type
            .if ( [edi].asym.mem_type == MT_TYPE )
                mov edx,[edi].asym.type
            .endif
            test [edi].asym.sflags,S_ISFAR
            setnz cl

            .if ( [edi].asym.mem_type != ti.mem_type || \
                  [edi].asym.is_ptr != ti.is_ptr || \
                  cl != ti.is_far || \
                  ( [edi].asym.is_ptr && [edi].asym.ptr_memtype != ti.ptr_memtype ) || \
                  edx != ti.symtype || \
                  ( langtype != LANG_NONE && [edi].asym.langtype != LANG_NONE && [edi].asym.langtype != langtype ) )

                .return( asmerr( 2004, token ) )
            .endif
        .endif

        or  [edi].asym.flags,S_ISDEFINED
        mov [edi].asym.Ofssize,ti.Ofssize

        .if ( ti.is_ptr == 0 && ti.Ofssize != ModuleInfo.Ofssize )
            mov al,[edi].asym.sflags
            or  al,ti.Ofssize
            mov ecx,[edi].asym.segm
            .if ( ecx )
                mov edx,[ecx].dsym.seginfo
            .endif
            mov [edi].asym.sflags,al
            and al,S_SEGOFSSIZE
            .if ( ecx && [edx].seg_info.Ofssize != al )
                mov [edi].asym.segm,NULL
            .endif
        .endif

        mov [edi].asym.mem_type,ti.mem_type
        mov [edi].asym.is_ptr,ti.is_ptr
        and [edi].asym.sflags,not S_ISFAR
        .if ( ti.is_far )
            or [edi].asym.sflags,S_ISFAR
        .endif
        mov [edi].asym.ptr_memtype,ti.ptr_memtype
        .if ( ti.mem_type == MT_TYPE )
            mov [edi].asym.type,ti.symtype
        .else
            mov [edi].asym.target_type,ti.symtype
        .endif

        HandleAltname( altname, edi )
        SetMangler( edi, langtype, mangle_type )

        imul ebx,i,asm_tok
        add ebx,tokenarray
        .if ( [ebx].token != T_FINAL )
            mov ecx,i
            inc ecx
            .if ( [ebx].token == T_COMMA &&  ( ecx < Token_Count ) )
                inc i
            .else
                .return( asmerr( 2008, [ebx].string_ptr ) )
            .endif
        .endif

     .until ( i >= Token_Count )

    .return( NOT_ERROR )

ExternDirective endp

; helper for COMM directive

MakeComm proc private uses edi name:string_t, sym:ptr asym, size:dword, count:dword, isfar:int_t

    mov edi,CreateComm( sym, name )
    .return .if ( edi == NULL )

    mov [edi].asym.total_length,count
    and [edi].asym.sflags,not S_ISFAR
    .if ( isfar )
        or [edi].asym.sflags,S_ISFAR
    .endif

    ; v2.04: don't set segment if communal is far and -Zg is set

    .if ( Options.masm_compat_gencode == FALSE || isfar == FALSE )
        mov [edi].asym.segm,CurrSeg
    .endif

    MemtypeFromSize( size, &[edi].asym.mem_type )

    ; v2.04: warning added ( Masm emits an error )
    ; v2.05: code active for 16-bit only

    .if ( ModuleInfo.Ofssize == USE16 )
        mov eax,size
        mul count
        .if ( eax > 0x10000 )
            asmerr( 8003, [edi].asym.name )
        .endif
    .endif
    mov eax,size
    mul count
    mov [edi].asym.total_size,eax
    .return( edi )

MakeComm endp

; define "communal" items
; syntax:
; COMM [langtype] [NEAR|FAR] label:type[:count] [, ... ]
; the size & count values must NOT be forward references!

CommDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

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
        add ebx,tokenarray

        ; get the -optional- distance ( near or far )

        mov isfar,FALSE

        .if ( [ebx].token == T_STYPE )

            .switch ( [ebx].tokval )

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
                add ebx,asm_tok
            .endsw
        .endif

        ; v2.08: ensure token is a valid id

        .if ( [ebx].token != T_ID )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif

        ; get the symbol name

        mov token,[ebx].string_ptr
        inc i
        add ebx,asm_tok

        ; go past the colon

        .if ( [ebx].token != T_COLON )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        inc i
        add ebx,asm_tok

        ; the evaluator cannot handle a ':' so scan for one first

        .for ( ecx = i, edx = ebx: ecx < Token_Count: ecx++, edx += asm_tok )
            .break .if ( [edx].asm_tok.token == T_COLON )
        .endf

        ; v2.10: expression evaluator isn't to accept forward references

        .if ( EvalOperand( &i, tokenarray, ecx, &opndx, EXPF_NOUNDEF ) == ERROR )
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
        add ebx,tokenarray

        .if ( [ebx].token == T_COLON )

            inc i

            ; get optional count argument
            ; v2.10: expression evaluator isn't to accept forward references

            .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
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

        mov edi,SymSearch( token )
        .if ( edi == NULL || [edi].asym.state == SYM_UNDEFINED )
            mov edi,MakeComm( token, edi, size, count, isfar )
            .if ( edi == NULL )
                .return( ERROR )
            .endif
        .elseif ( [edi].asym.state != SYM_EXTERNAL || !( [edi].asym.sflags & S_ISCOM ) )
            .return( asmerr( 2005, [edi].asym.name ) )
        .else
            mov eax,[edi].asym.total_size
            cdq
            div [edi].asym.total_length
            mov ecx,count
            .if ( ecx != [edi].asym.total_length || size != eax )
                .return( asmerr( 2007, szCOMM, [edi].asym.name ) )
            .endif
        .endif
        or [edi].asym.flags,S_ISDEFINED
        SetMangler( edi, langtype, mangle_type )

        imul ebx,i,asm_tok
        add ebx,tokenarray
        .if ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )
            .return( asmerr( 2008, [ebx].tokpos ) )
        .endif
    .endf
    .return( NOT_ERROR )

CommDirective endp

; syntax: PUBLIC [lang_type] name [, ...]

PublicDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

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
        add ebx,tokenarray

        .if ( [ebx].token != T_ID )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif

        ; get the symbol name

        mov token,[ebx].string_ptr
        inc i
        add ebx,asm_tok

        ; Add the public name

        mov edi,SymSearch( token )
        .if ( Parse_Pass == PASS_1 )
            .if ( edi == NULL )
                .if ( SymCreate( token ) )
                    mov edi,eax
                    sym_add_table( &SymTables[TAB_UNDEF*symbol_queue], edi )
                .else
                    .return( ERROR ) ; name was too long
                .endif
            .endif
            mov skipitem,FALSE
        .else
            .if ( edi == NULL || [edi].asym.state == SYM_UNDEFINED )
                asmerr( 2006, token )
            .endif
        .endif
        .if ( edi )
            .switch ( [edi].asym.state )
            .case SYM_UNDEFINED
                .endc
            .case SYM_INTERNAL
                .if ( [edi].asym.flags & S_SCOPED )
                    asmerr( 2014, [edi].asym.name )
                    mov skipitem,TRUE
                .endif
                .endc
            .case SYM_EXTERNAL
                .if ( [edi].asym.sflags & S_ISCOM )
                    asmerr( 2014, [edi].asym.name )
                    mov skipitem,TRUE
                .elseif ( !( [edi].asym.sflags & S_WEAK ) )
                    ; for EXTERNs, emit a different error msg
                    asmerr( 2005, [edi].asym.name )
                    mov skipitem,TRUE
                .endif
                .endc
            .default
                asmerr( 2014, [edi].asym.name )
                mov skipitem,TRUE
            .endsw
            .if ( Parse_Pass == PASS_1 && skipitem == FALSE )
                .if ( !( [edi].asym.flags & S_ISPUBLIC ) )
                    or [edi].asym.flags,S_ISPUBLIC
                    AddPublicData( edi ) ; put it into the public table
                .endif
                SetMangler( edi, langtype, mangle_type )
            .endif
        .endif

        .if ( [ebx].token != T_FINAL )
            .if ( [ebx].token == T_COMMA )
                mov ecx,i
                inc ecx
                .if ( ecx < Token_Count )
                    inc i
                .endif
            .else
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif
        .endif

    .until ( i >= Token_Count )
    .return( NOT_ERROR )

PublicDirective endp

    end
