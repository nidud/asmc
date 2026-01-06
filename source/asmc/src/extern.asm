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
include parser.inc
include expreval.inc
include types.inc
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

; There's a deliberate Masm incompatibility in JWasm's implementation of
; EXTERN(DEF): the current segment is stored in the definition, making the
; assembler assume that, in case the symbol's distance is FAR, that it's
; in the current segment ( thus allowing some code optimisation ).
; To behave exactly like Masm in this regard option -Zg has to be set - or
; enable the switch below.

define MASM_NOSEGSTORE 0 ; 1 is Masm compatible

szCOMM equ <"COMM">

define mangle_type NULL

    .code

; create external.
; sym must be NULL or of state SYM_UNDEFINED!

CreateExternal proc fastcall private uses rsi sym:asym_t, name:string_t, weak:char_t

    mov rsi,rcx
    .if ( rsi == NULL )
        mov rsi,SymCreate( rdx )
    .else
        sym_remove_table( &SymTables[TAB_UNDEF], rsi )
    .endif

    .if ( rsi )
        mov [rsi].asym.state,SYM_EXTERNAL
        mov [rsi].asym.segoffsize,MODULE.Ofssize
        mov [rsi].asym.iscomm,0
        mov [rsi].asym.weak,0
        .if ( weak )
            mov [rsi].asym.weak,1
        .endif
        sym_add_table( &SymTables[TAB_EXT], rsi ) ; add EXTERNAL
    .endif
    .return( rsi )

CreateExternal endp


; create communal.
; sym must be NULL or of state SYM_UNDEFINED!

CreateComm proc fastcall private uses rsi sym:asym_t, name:string_t

    mov rsi,rcx
    .if ( rsi == NULL )
        mov rsi,SymCreate( rdx )
    .else
        sym_remove_table( &SymTables[TAB_UNDEF], rsi )
    .endif

    .if ( rsi )

        mov [rsi].asym.state,SYM_EXTERNAL
        mov [rsi].asym.segoffsize,MODULE.Ofssize
        mov [rsi].asym.is_far,0
        mov [rsi].asym.weak,0
        mov [rsi].asym.iscomm,1
        sym_add_table( &SymTables[TAB_EXT], rsi ) ; add EXTERNAL
    .endif
    .return( rsi )

CreateComm endp


; create a prototype.
; used by PROTO, EXTERNDEF and EXT[E]RN directives.

    assume rbx:token_t

CreateProto proc __ccall private uses rsi rdi rbx i:int_t, tokenarray:token_t, name:string_t, langtype:byte

    mov rsi,SymFind(name)

    ; the symbol must be either NULL or state
    ; - SYM_UNDEFINED
    ; - SYM_EXTERNAL + isproc == FALSE ( previous EXTERNDEF )
    ; - SYM_EXTERNAL + isproc == TRUE ( previous PROTO )
    ; - SYM_INTERNAL + isproc == TRUE ( previous PROC )

    .if ( rsi == NULL || [rsi].asym.state == SYM_UNDEFINED ||
          ( [rsi].asym.state == SYM_EXTERNAL && ( [rsi].asym.weak ) &&
            !( [rsi].asym.isproc ) ) )

        .if ( CreateProc( rsi, name, SYM_EXTERNAL ) == NULL )
            .return ; name was probably invalid
        .endif
        mov rsi,rax

    .elseif ( !( [rsi].asym.isproc ) )
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

        mov rdi,SymFind( [rbx].string_ptr )
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
        mov [rsi].asym.dll,MODULE.CurrDll
    .else
        mov [rsi].asym.isdefined,1
    .endif
    .return( rsi )

CreateProto endp


; externdef [ attr ] symbol:type [, symbol:type,...]

ExterndefDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local token:string_t
  local langtype:byte
  local isnew:char_t
  local ti:qualified_type

    inc i ; skip EXTERNDEF token

    .repeat

        mov ti.Ofssize,MODULE.Ofssize

        ; get the symbol language type if present

        mov langtype,MODULE.langtype
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
        mov rsi,SymFind( token )

        mov ti.mem_type,MT_EMPTY
        mov ti.size,0
        mov ti.is_ptr,0
        mov ti.is_far,FALSE
        mov ti.ptr_memtype,MT_EMPTY
        mov ti.symtype,NULL
        mov ti.Ofssize,MODULE.Ofssize

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

        .elseif ( [rsi].asym.state != SYM_INTERNAL && [rsi].asym.state != SYM_EXTERNAL )

            ; v2.16: externdef must be intern or extern

            .return( asmerr( 2014, [rsi].asym.name ) )
        .endif

        ; new symbol?

        mov rdi,ti.symtype

        .if ( isnew )

            ; v2.05: added to accept type prototypes

            .if ( ti.is_ptr == 0 && rdi && [rdi].asym.isproc )

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
if MASM_NOSEGSTORE
                .endc .if ( MODULE.masm_compat_gencode )
else
                .endc
endif
                ; fall through
            .default
                mov [rsi].asym.segm,CurrSeg
            .endsw

            mov [rsi].asym.Ofssize,ti.Ofssize
            mov al,ti.Ofssize

            .if ( ti.is_ptr == 0 && al != MODULE.Ofssize )

                mov [rsi].asym.segoffsize,al
                mov rcx,[rsi].asym.segm
                .if ( rcx )
                    mov rdx,[rcx].asym.seginfo
                    .if ( al != [rdx].seg_info.Ofssize )
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

            .if ( ti.is_ptr == 0 && rdi && [rdi].asym.isproc )

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
if 1
            ; v2.18: code moved from below to this place
            ; this covers the case where the externdef is located BEHIND
            ; the label that is to become public.
            ; It's still a bit doubtful for PROCs, because the PROC directive
            ; should know better about the visibility status of the procedure.
            ; So if the PROC has been explicitely marked as private, the
            ; externdef doesn't care. But that's what masm (6/8) does...

            .if ( [rsi].asym.state == SYM_INTERNAL && !( [rsi].asym.ispublic ) )

                mov [rsi].asym.ispublic,1
                AddPublicData( rsi )
            .endif
endif
        .endif
        mov [rsi].asym.isdefined,1

if 0
        ; v2.18: removed, because it's a bug.
        ; 1. adding a public after pass one is something that should NOT be done.
        ; If output format is OMF, the publics are written after pass one and then
        ; again when all is finished. If the number of publics differ for the second
        ; write, the object module may become invalid!
        ; 2. if FASTPASS is on, there's a good chance that the EXTERNDEF directive
        ; code won't run after pass one - if the FASTPASS's line store feature hasn't
        ; been triggered yet ( that is, no code or data definition BEFORE the EXTERNDEF ).
        ; 3. the EXTERNDEF directive running in pass 2 surely cannot know better than
        ; the PROC directive what the visibility status of the procedure is supposed to be.

        .if ( [rsi].asym.state == SYM_INTERNAL && !( [rsi].asym.ispublic ) )

            mov [rsi].asym.ispublic,1
            AddPublicData(rsi)
        .endif
endif
        .if ( [rbx].token != T_FINAL )
            .if ( [rbx].token == T_COMMA )
                mov eax,i
                inc eax
                .if ( eax < TokenCount )
                    inc i
                    add rbx,asm_tok
                .endif
            .else
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif
        .endif
    .until ( i >= TokenCount )
    .return( NOT_ERROR )

ExterndefDirective endp


; PROTO directive.
; <name> PROTO <params> is semantically identical to:
; EXTERNDEF <name>: PROTO <params>

ProtoDirective proc __ccall uses rbx i:int_t, tokenarray:token_t

    ldr rbx,tokenarray
    .if ( Parse_Pass != PASS_1 )

        ; v2.04: set the "defined" flag

        .if ( SymFind( [rbx].string_ptr ) )
            .if ( [rax].asym.isproc )
                mov [rax].asym.isdefined,1
            .endif
        .endif
        .return( NOT_ERROR )
    .endif
    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [rbx+rcx].string_ptr ) )
    .endif
    .if CreateProto( 2, tokenarray, [rbx].string_ptr, MODULE.langtype )
        mov eax,NOT_ERROR
    .else
        mov eax,ERROR
    .endif
    ret

ProtoDirective endp


; helper for EXTERN directive.
; also used to create 16-bit floating-point fixups.
; sym must be NULL or of state SYM_UNDEFINED!

MakeExtern proc __ccall name:string_t, mem_type:byte, vartype:asym_t, sym:asym_t, Ofssize:byte

    .if ( CreateExternal( sym, name, FALSE ) == NULL )

        .return
    .endif
    mov rcx,rax

    .if ( mem_type != MT_EMPTY &&
        ( Options.masm_compat_gencode == FALSE || mem_type != MT_FAR ) )
        mov [rcx].asym.segm,CurrSeg
    .endif
    mov [rcx].asym.isdefined,1
    mov [rcx].asym.mem_type,mem_type
    mov [rcx].asym.segoffsize,Ofssize
    mov [rcx].asym.type,vartype
    mov rax,rcx
    ret

MakeExtern endp


; handle optional alternate names in EXTERN directive

HandleAltname proc __ccall private uses rsi rdi rbx altname:string_t, sym:asym_t

    mov rsi,sym

    .if ( altname && [rsi].asym.state == SYM_EXTERNAL )

        mov rdi,SymFind( altname )

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
                .if ( [rdi].asym.state == SYM_INTERNAL && !( [rdi].asym.ispublic ) )
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
                sym_add_table( &SymTables[TAB_UNDEF], rdi )
            .endif

            ; make sure the alt symbol becomes strong if it is an external
            ; v2.11: don't do this for OMF ( maybe neither for COFF/ELF? )

            .if ( Options.output_format != OFORMAT_OMF )
                mov [rdi].asym.used,1
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

ExternDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local langtype:byte
  local ti:qualified_type
  local altname:string_t
  local token:string_t

    inc i ; skip EXT[E]RN token

    .repeat

        mov altname,NULL

        ; get the symbol language type if present

        mov langtype,MODULE.langtype
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
        mov rdi,SymFind( token )

        mov ti.mem_type,MT_EMPTY
        mov ti.size,0
        mov ti.is_ptr,0
        mov ti.is_far,FALSE
        mov ti.ptr_memtype,MT_EMPTY
        mov ti.symtype,NULL
        mov ti.Ofssize,MODULE.Ofssize

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
                mov [rdi].asym.weak,0
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
                mov dl,MODULE.Ofssize
            .endif

            .if ( MakeExtern( token, ti.mem_type, rcx, rdi, dl ) == NULL )
                .return( ERROR )
            .endif
            mov rdi,rax

            ; v2.05: added to accept type prototypes

            mov rsi,ti.symtype

            .if ( ti.is_ptr == 0 && rsi && [rsi].asym.isproc )

                CreateProc( rdi, NULL, SYM_EXTERNAL )

                ; v2.09: reset the weak bit that has been set inside CreateProc()

                mov [rdi].asym.weak,0

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
                ; v2.16: change error msg to what masm displays

                .if ( [rdi].asym.state != SYM_EXTERNAL )
                    .return( asmerr( 2014, token ) )
                .endif
if MASM_EXTCOND
            .endif
endif
            ; v2.05: added to accept type prototypes

            mov rsi,ti.symtype
            .if ( ti.is_ptr == 0 && rsi && [rsi].asym.isproc )

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

        mov [rdi].asym.isdefined,1
        mov [rdi].asym.Ofssize,ti.Ofssize

        .if ( ti.is_ptr == 0 && al != MODULE.Ofssize )

            mov [rdi].asym.segoffsize,al
            mov rcx,[rdi].asym.segm
            .if ( rcx )
                mov rdx,[rcx].asym.seginfo
            .endif
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
            .if ( [rbx].token == T_COMMA &&  ( ecx < TokenCount ) )
                inc i
            .else
                .return( asmerr( 2008, [rbx].string_ptr ) )
            .endif
        .endif
     .until ( i >= TokenCount )
     .return( NOT_ERROR )

ExternDirective endp


; helper for COMM directive

MakeComm proc __ccall private uses rdi name:string_t, sym:asym_t, size:dword, count:dword, isfar:uchar_t

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

    .if ( MODULE.Ofssize == USE16 )
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

CommDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local token:string_t
  local isfar:byte
  local tmp:int_t
  local size:uint_32  ; v2.12: changed from 'int' to 'uint_32'
  local count:uint_32 ; v2.12: changed from 'int' to 'uint_32'
  local sym:asym_t
  local type:asym_t ; v2.17: remember type in case one was given
  local opndx:expr
  local langtype:byte

    inc i ; skip COMM token

    .for ( : i < TokenCount: i++ )

        ; get the symbol language type if present

        mov langtype,MODULE.langtype
        GetLangType( &i, tokenarray, &langtype )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        ; get the -optional- distance ( near or far )

        mov isfar,FALSE

        .if ( [rbx].token == T_STYPE )

            mov eax,[rbx].tokval
            .switch eax

            .case T_FAR
            .case T_FAR16
            .case T_FAR32

                .if ( MODULE._model == MODEL_FLAT )
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

        .for ( ecx = i, rdx = rbx: ecx < TokenCount: ecx++, rdx += asm_tok )
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
            EmitConstError()
        .elseif ( opndx.uvalue == 0 )
            asmerr( 2090 )
        .endif

        mov size,opndx.uvalue
        mov type,opndx.type     ; v2.17: save type
        mov count,1

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( [rbx].token == T_COLON )

            inc i

            ; get optional count argument
            ; v2.10: expression evaluator isn't to accept forward references

            .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF ) == ERROR )
                .return( ERROR )
            .endif

            ; v2.03: a string constant is acceptable!
            ; v2.12: check for too large value added

            .if ( opndx.kind != EXPR_CONST )
                asmerr( 2026 )
            .elseif ( opndx.hvalue != 0 && opndx.hvalue != -1 )
                EmitConstError()
            .elseif ( opndx.uvalue == 0 )
                asmerr( 2090 )
            .endif

            mov count,opndx.uvalue
        .endif

        mov rdi,SymFind( token )
        .if ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )
            mov rdi,MakeComm( token, rdi, size, count, isfar )
            .if ( rdi == NULL )
                .return( ERROR )
            .endif
            mov [rdi].asym.type,type ; v2.17 added
        .elseif ( [rdi].asym.state != SYM_EXTERNAL || !( [rdi].asym.iscomm ) )
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
        mov [rdi].asym.isdefined,1
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

PublicDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local token:string_t
  local sym:asym_t
  local skipitem:sbyte
  local langtype:byte
  local isexport:byte

    inc i ; skip PUBLIC directive

    .repeat

        ; read the optional language type

        mov langtype,MODULE.langtype
        GetLangType( &i, tokenarray, &langtype )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( [rbx].token != T_ID )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif

        ; v2.19: syntax extension: scan for optional EXPORT attribute

        mov isexport,FALSE
        .if ( Options.strict_masm_compat == FALSE && [rbx+asm_tok].token == T_ID )
            .ifd ( tstricmp( [rbx].string_ptr, "EXPORT" ) == 0 )
                mov isexport,TRUE
                inc i
                add rbx,asm_tok
            .endif
        .endif

        ; get the symbol name

        mov token,[rbx].string_ptr
        inc i
        add rbx,asm_tok

        ; Add the public name

        mov rdi,SymFind( token )
        .if ( Parse_Pass == PASS_1 )
            .if ( rdi == NULL )
                .if ( SymCreate( token ) )
                    mov rdi,rax
                    sym_add_table( &SymTables[TAB_UNDEF], rdi )
                .else
                    .return( ERROR ) ; name was too long
                .endif
            .endif
            mov skipitem,FALSE
        .elseif ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )
            asmerr( 2006, token )
        .endif
        .if ( rdi )
            movzx eax,[rdi].asym.state
            .switch eax
            .case SYM_UNDEFINED
                .if ( isexport )
                    mov [rdi].asym.isexport,1
                .endif
                .endc
            .case SYM_INTERNAL
                .if ( [rdi].asym.scoped )
                    asmerr( 2014, [rdi].asym.name )
                    mov skipitem,TRUE
                .endif
                .if ( isexport )
                    mov [rdi].asym.isexport,1
                .endif
                .endc
            .case SYM_EXTERNAL
                .if ( [rdi].asym.iscomm )
                    asmerr( 2014, [rdi].asym.name )
                    mov skipitem,TRUE
                .elseif ( !( [rdi].asym.weak ) )
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
                .if ( !( [rdi].asym.ispublic ) )
                    mov [rdi].asym.ispublic,1
                    AddPublicData( rdi ) ; put it into the public table
                .endif
                SetMangler( rdi, langtype, mangle_type )
            .endif
        .endif

        .if ( [rbx].token != T_FINAL )
            .if ( [rbx].token == T_COMMA )
                mov ecx,i
                inc ecx
                .if ( ecx < TokenCount )
                    inc i
                .endif
            .else
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif
        .endif
    .until ( i >= TokenCount )
    .return( NOT_ERROR )

PublicDirective endp

    end
