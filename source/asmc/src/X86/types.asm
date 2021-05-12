; TYPES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: STRUCT, UNION, RECORD and TYPEDEF directives.
;

include asmc.inc
include memalloc.inc
include parser.inc
include segment.inc
include proc.inc
include input.inc
include tokenize.inc
include types.inc
include expreval.inc
include label.inc
include listing.inc
include fastpass.inc

define ANYNAME 0
define TYPEOPT 0

.data

CurrStruct ptr dsym 0
redef_struct ptr dsym 0
;; text constants for 'Non-benign <x> redefinition' error msg
define szStructure <"structure">
define szRecord <"record">

define szNonUnique <"NONUNIQUE">

.code

TypesInit proc

    mov CurrStruct,NULL
    mov redef_struct,NULL
    ret

TypesInit endp

;; create a SYM_TYPE symbol.
;; <sym> must be NULL or of state SYM_UNDEFINED.
;; <name> and <global> are only used if <sym> is NULL.
;; <name> might be an empty string.

CreateTypeSymbol proc uses esi edi sym:ptr asym, name:string_t, global:int_t

    mov esi,sym
    .if ( esi )
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], esi )
    .else
        .if ( global )
            SymCreate( name )
        .else
            SymAlloc( name )
        .endif
        mov esi,eax
    .endif

    .if ( esi )
        mov [esi].asym.state,SYM_TYPE
        mov [esi].asym.typekind,TYPE_NONE
        mov edi,LclAlloc( sizeof( struct_info ) )
        mov [esi].dsym.structinfo,edi
        mov [edi].struct_info.head,NULL
        mov [edi].struct_info.tail,NULL
        mov [edi].struct_info.alignment,0
        mov [edi].struct_info.flags,0
    .endif
    .return( esi )
CreateTypeSymbol endp

;; search a name in a struct's fieldlist

    assume ebx:ptr sfield

SearchNameInStruct proc uses esi edi ebx tstruct:ptr asym, name:string_t,
    poffset:ptr uint_32, level:int_t

    mov edi,strlen( name )
    xor esi,esi

    mov ecx,tstruct
    mov edx,[ecx].dsym.structinfo
    mov ebx,[edx].struct_info.head

    .if ( level >= MAX_STRUCT_NESTING )

        asmerr( 1007 )
        .return( NULL )
    .endif

    inc level

    .for ( : ebx : ebx = [ebx].next )

        ;; recursion: if member has no name, check if it is a structure
        ;; and scan this structure's fieldlist then
        mov eax,[ebx].sym.name
        .if ( byte ptr [eax] == 0 )
            ;; there are 2 cases: an anonymous inline struct ...
            .if ( [ebx].sym.state == SYM_TYPE )
                .if ( SearchNameInStruct( ebx, name, poffset, level ) )
                    mov esi,eax
                    mov ecx,poffset
                    .if ecx
                        add [ecx],[ebx].sym.offs
                    .endif
                    .break
                .endif
            ;; or an anonymous structured field
            .elseif ([ebx].sym.mem_type == MT_TYPE )
                .if ( SearchNameInStruct( [ebx].sym.type, name, poffset, level ) )
                    mov esi,eax
                    mov ecx,poffset
                    .if ecx
                        add [ecx],[ebx].sym.offs
                    .endif
                    .break
                .endif
            .endif
        .elseif ( di == [ebx].sym.name_size )
            .if ( SymCmpFunc( name, [ebx].sym.name, edi ) == 0 )
                mov esi,ebx
                .break
            .endif
        .endif
    .endf
    .return( esi )

SearchNameInStruct endp

;; check if a struct has changed

    assume edi:ptr sfield

AreStructsEqual proc private uses edi ebx newstr:ptr dsym, oldstr:ptr dsym

    mov eax,oldstr
    mov ecx,[eax].dsym.structinfo
    mov ebx,[ecx].struct_info.head

    mov eax,newstr
    mov ecx,[eax].dsym.structinfo
    mov edi,[ecx].struct_info.head

    ;; kind of structs must be identical
    .if ( [ebx].sym.typekind != [edi].sym.typekind )
        .return( FALSE )
    .endif

    .for ( : ebx : ebx = [ebx].next, edi = [edi].next )
        .if ( !edi )
            .return( FALSE )
        .endif
        ;; for global member names, don't check the name if it's ""
        mov eax,[edi].sym.name

        .if ( ModuleInfo.oldstructs && byte ptr [eax] == 0 )
            ;
        .elseif ( strcmp( [ebx].sym.name, [edi].sym.name ) )
            .return( FALSE )
        .endif
        .if ( [ebx].sym.offs != [edi].sym.offs )
            .return( FALSE )
        .endif
        .if ( [ebx].sym.total_size != [edi].sym.total_size )
            .return( FALSE )
        .endif
    .endf
    .if ( edi )
        .return( FALSE )
    .endif
    .return( TRUE )

AreStructsEqual endp

;; handle STRUCT, STRUC, UNION directives
;; i = index of directive token

    assume ebx:ptr asm_tok
    assume edi:nothing

StructDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local alignment:uint_t
  local offs:uint_t
  local typekind:byte

    ;; top level structs/unions must have an identifier at pos 0.
    ;; for embedded structs, the directive must be at pos 0,
    ;; an identifier is optional then.

    mov ebx,tokenarray
    mov esi,[ebx].string_ptr
    imul ecx,i,asm_tok
    add ebx,ecx

    mov typekind,TYPE_STRUCT
    .if ( [ebx].tokval == T_UNION )
        mov typekind,TYPE_UNION
    .endif

    mov eax,CurrStruct
    .if ( ( eax == NULL && i != 1 ) || ( eax != NULL && i != 0 ) )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif

    mov eax,1
    mov cl,ModuleInfo.fieldalign
    shl eax,cl
    mov alignment,eax

    inc i ;; go past STRUCT/UNION
    add ebx,16

    .if ( i == 1 ) ;; embedded struct?
        ;; scan for the optional name
        lea esi,@CStr("")
if ANYNAME
        ;; the name might be a reserved word!
        ;; Masm won't allow those.
else
        .if ( [ebx].token == T_ID )
endif
            mov esi,[ebx].string_ptr
            inc i
            add ebx,16
        .endif
    .endif

    ;; get an optional alignment argument: 1,2,4,8,16 or 32
    .if ( CurrStruct == NULL && [ebx].token != T_FINAL )

        .new opndx:expr

        ;; get the optional alignment parameter.
        ;; forward references aren't accepted, but EXPF_NOUNDEF isn't used here!

        .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) != ERROR )
            ;; an empty expression is accepted
            mov ecx,opndx.sym
            .if ( opndx.kind == EXPR_EMPTY )

            .elseif ( opndx.kind != EXPR_CONST )
                ;; v2.09: better error msg
                .if ( ecx && [ecx].asym.state == SYM_UNDEFINED )
                    asmerr( 2006, [ecx].asym.name )
                .else
                    asmerr( 2026 )
                .endif
            .elseif( opndx.value > MAX_STRUCT_ALIGN )
                asmerr( 2064 )
            .else
                .for( eax = 1: eax < opndx.value: eax <<= 1 )
                .endf
                .if ( eax != opndx.value )
                    asmerr( 2063, opndx.value )
                .else
                    mov alignment,opndx.value
                .endif
            .endif
        .endif
        imul ebx,i,asm_tok
        add ebx,tokenarray

        ;; there might also be the NONUNIQUE parameter
        .if ( [ebx].token == T_COMMA )
            inc i
            add ebx,16
            .if ( [ebx].token == T_ID && \
                ( _stricmp( [ebx].string_ptr, szNonUnique ) == 0 ) )
                ;; currently NONUNIQUE is ignored
                asmerr( 8017, szNonUnique )
                inc i
                add ebx,16
            .endif
        .endif
    .endif
    .if ( [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].tokpos ) )
    .endif

    ;; does struct have a name?
    .if ( byte ptr [esi] )
        .if ( CurrStruct == NULL )
            ;; the "top-level" struct is part of the global namespace
            mov edi,SymSearch( esi )
        .else
            mov edi,SearchNameInStruct( CurrStruct, esi, &offs, 0 )
        .endif
    .else
        mov edi,NULL ;; anonymous struct
    .endif

    .if ( ModuleInfo.list )
        mov ecx,CurrStruct
        .if ( ecx )
            LstWrite( LSTTYPE_STRUCT, [ecx].asym.total_size, NULL )
        .else
            LstWrite( LSTTYPE_STRUCT, 0, NULL )
        .endif
    .endif

    ;; if pass is > 1, update struct stack + CurrStruct.offset and exit
    .if ( Parse_Pass > PASS_1 )

        ;; v2.04 changed. the previous implementation was insecure.
        ;; See also change in data.c, behind CreateStructField().
        mov ecx,CurrStruct
        .if ( ecx )
            mov ecx,[ecx].dsym.structinfo
            mov edx,[ecx].struct_info.tail
            mov edi,[edx].sfield.sym.type
            mov [ecx].struct_info.tail,[edx].sfield.next
        .endif
        mov ecx,[edi].dsym.structinfo
        mov eax,[ecx].struct_info.head
        mov [ecx].struct_info.tail,eax
        mov [edi].asym.offs,0
        or  [edi].asym.flags,S_ISDEFINED
        mov [edi].dsym.next,CurrStruct
        mov CurrStruct,edi
        .return( NOT_ERROR )
    .endif

    .if ( edi == NULL )

        ;; embedded or global STRUCT?
        .if ( CurrStruct == NULL )
            mov edi,CreateTypeSymbol( NULL, esi, TRUE )
        .else

            ;; an embedded struct is split in an anonymous STRUCT type
            ;; and a struct field with/without name

            mov edi,CreateTypeSymbol( NULL, esi, FALSE )

            ;; v2: don't create the struct field here. First the
            ;; structure must be read in ( because of alignment issues

            mov ecx,CurrStruct
            mov ecx,[ecx].dsym.structinfo

            mov alignment,[ecx].struct_info.alignment
        .endif

    .elseif( [edi].asym.state == SYM_UNDEFINED )

        ;; forward reference
        xor eax,eax
        .if ( CurrStruct == NULL )
            inc eax
        .endif
        CreateTypeSymbol( edi, NULL, eax )

    .elseif( [edi].asym.state == SYM_TYPE && CurrStruct == NULL )

        .switch ( [edi].asym.typekind )
        .case TYPE_STRUCT
        .case TYPE_UNION

            ;; if a struct is redefined as a union ( or vice versa )
            ;; do accept the directive and just check if the redefinition
            ;; is compatible (usually it isn't)

            mov redef_struct,edi
            mov edi,CreateTypeSymbol( NULL, esi, FALSE )
            .endc
        .case TYPE_NONE ;; TYPE_NONE is forward reference
            .endc
        .default
            .return( asmerr( 2005, [edi].asym.name ) )
        .endsw

    .else
        .return( asmerr( 2005, [edi].asym.name ) )
    .endif

    mov [edi].asym.offs,0
    mov [edi].asym.typekind,typekind

    mov ecx,[edi].dsym.structinfo
    mov [ecx].struct_info.alignment,alignment
    or [ecx].struct_info.flags,SI_ISOPEN
    .if ( CurrStruct )
        or [ecx].struct_info.flags,SI_ISINLINE
    .endif

    mov [edi].dsym.next,CurrStruct

    .if ( ModuleInfo.ComStack )

        mov ebx,ModuleInfo.ComStack
        assume ebx:ptr com_item

        mov  ecx,strlen( [ebx].class )
        mov  edx,edi
        mov  edi,[ebx].class
        repz cmpsb
        mov  edi,edx
        .ifz
            mov eax,[esi]
            .if ( al == 0 )
                mov [ebx].sym,edi
                .switch ( [ebx].cmd )
                .case T_DOT_CLASS
                    or [edi].asym.flag2,S_CLASS
                    .endc
                .case T_DOT_COMDEF
                    or [edi].asym.flag2,S_COMDEF
                    .endc
                .case T_DOT_TEMPLATE
                    or [edi].asym.flag2,S_TEMPLATE
                    .endc
                .endsw
            .elseif ( eax == 'lbtV' && byte ptr [esi+4] == 0 )
                mov ecx,[ebx].sym
                or  [ecx].asym.flag2,S_VTABLE
                mov [ecx].asym.vtable,edi
                mov [edi].asym.class,ecx
                or  [edi].asym.flag2,S_ISVTABLE
            .endif
        .endif
        assume ebx:ptr asm_tok
    .endif
    mov CurrStruct,edi

    .return( NOT_ERROR )

StructDirective endp

;; handle ENDS directive when a struct/union definition is active

EndstructDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

    mov edi,CurrStruct ;; cannot be NULL

    ;; if pass is > 1 just do minimal work
    .if ( Parse_Pass > PASS_1 )
        mov [edi].asym.offs,0
        mov ebx,[edi].asym.total_size
        mov CurrStruct,[edi].dsym.next
        .if ( CurrStruct )
            UpdateStructSize( edi )
        .endif
        .if ( CurrFile[LST*4] )
            LstWrite( LSTTYPE_STRUCT, ebx, edi )
        .endif
        .return( NOT_ERROR )
    .endif

    ;; syntax is either "<name> ENDS" (i=1) or "ENDS" (i=0).
    ;; first case must be top level (next=NULL), latter case must NOT be top level (next!=NULL)
    mov ebx,tokenarray
    .if ( ( i == 1 && [edi].dsym.next == NULL ) || \
          ( i == 0 && [edi].dsym.next != NULL ) )

    .else
        lea edx,@CStr("")
        .if ( i == 1 )
            mov edx,[ebx].asm_tok.string_ptr
        .endif
        .return( asmerr( 1010, edx ) )
    .endif

    .if ( i == 1 ) ;; an global struct ends with <name ENDS>
        .if ( SymCmpFunc( [ebx].string_ptr, [edi].asym.name, [edi].asym.name_size ) != 0 )
            ;; names don't match
            .return( asmerr( 1010, [ebx].string_ptr ) )
        .endif
    .endif

    inc i ;; go past ENDS
    imul ecx,i,asm_tok
    add ebx,ecx

    ;; v2.07: if ORG was used inside the struct, the struct's size
    ;; has to be calculated now - there may exist negative offsets.
    mov esi,[edi].dsym.structinfo

    .if ( [esi].struct_info.flags & SI_ORGINSIDE )
        .for ( ecx = 0, edx = [esi].struct_info.head: edx: edx = [edx].sfield.next )
            .if ( [edx].sfield.sym.offs < ecx )
                mov ecx,[edx].sfield.sym.offs
            .endif
        .endf
        mov eax,[edi].asym.total_size
        sub eax,ecx
        mov [edi].asym.total_size,eax
    .endif

    ;; Pad bytes at the end of the structure.

    ;; v2.02: this is to be done in any case, whether -Zg is set or not
    movzx edx,[esi].struct_info.alignment
    .if ( edx > 1 )
        mov eax,[edi].asym.max_mbr_size
        .if ( eax == 0 )
            inc eax
        .endif
        .if ( eax > edx )
            mov eax,edx
        .endif
        mov ecx,eax
        neg ecx
        add eax,[edi].asym.total_size
        dec eax
        and eax,ecx
        mov [edi].asym.total_size,eax
    .endif

    and [esi].struct_info.flags,not SI_ISOPEN
    or  [edi].asym.flags,S_ISDEFINED

    ;; if there's a negative offset, size will be wrong!
    mov esi,[edi].asym.total_size

    ;; reset offset, it's just used during the definition
    mov [edi].asym.offs,0

    mov CurrStruct,[edi].dsym.next
    .if ( i == 1 )

        mov eax,[edi].asym.name
        .if ( byte ptr [eax] == 0 )
            xor eax,eax
        .endif
        CreateStructField( -1, NULL, eax, MT_TYPE, edi, [edi].asym.total_size )
        mov ecx,[edi].asym.total_size
        mov [eax].asym.total_size,ecx
        mov [edi].asym.name,&@CStr("") ; the type becomes anonymous
        mov [edi].asym.name_size,0
    .endif

    .if ( CurrFile[LST*4] )
        LstWrite( LSTTYPE_STRUCT, si, edi )
    .endif

    ;; to allow direct structure access
    mov eax,[edi].asym.total_size
    .switch ( eax )
    .case 1:  mov [edi].asym.mem_type,MT_BYTE   : .endc
    .case 2:  mov [edi].asym.mem_type,MT_WORD   : .endc
    .case 4:  mov [edi].asym.mem_type,MT_DWORD  : .endc
    .case 6:  mov [edi].asym.mem_type,MT_FWORD  : .endc
    .case 8
        mov [edi].asym.mem_type,MT_QWORD
        .endc
    .default
        mov [edi].asym.mem_type,MT_EMPTY
    .endsw

    ;; reset redefine
    .if ( CurrStruct == NULL )
        .if ( redef_struct )
            .if ( AreStructsEqual( edi, redef_struct ) == FALSE )
                asmerr( 2007, szStructure, [edi].asym.name )
            .endif
            SymFree( edi )
            mov redef_struct,NULL
        .endif
    .else

        mov ecx,CurrStruct
        mov eax,[edi].asym.max_mbr_size
        .if ( eax > [ecx].asym.max_mbr_size )
            mov [ecx].asym.max_mbr_size,eax
        .endif

        UpdateStructSize( edi )
    .endif
    .if ( [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif
    .return( NOT_ERROR )
EndstructDirective endp

;; v2.06: new function to check fields of anonymous struct members

    assume edi:ptr sfield

CheckAnonymousStruct proc fastcall private uses edi type_ptr:ptr dsym

    mov ecx,[ecx].dsym.structinfo
    .for ( edi = [ecx].struct_info.head : edi : edi = [edi].next )
        mov eax,[edi].sym.name
        .if ( byte ptr [eax] )
            SearchNameInStruct( CurrStruct, [edi].sym.name, 0, 0 )
            .if ( eax )
                .return( asmerr( 2005, [eax].asym.name ) )
            .endif
        .elseif ( [edi].sym.type )
            mov eax,[edi].sym.type
            .if ( [eax].asym.typekind == TYPE_STRUCT || \
                  [eax].asym.typekind == TYPE_UNION )
                .if ( CheckAnonymousStruct( eax ) == ERROR )
                    .return( ERROR )
                .endif
            .endif
        .endif
    .endf
    .return( NOT_ERROR )

CheckAnonymousStruct endp

;; CreateStructField() - creates a symbol of state SYM_STRUCT_FIELD.
;; this function is called in pass 1 only.
;; - loc: initializer index location, -1 means no initializer (is an embedded struct)
;; - name: field name, may be NULL
;; - mem_type: mem_type of item
;; - vartype: user-defined type of item if memtype is MT_TYPE
;; - size: size of type - used for alignment only

    assume esi:ptr struct_info

CreateStructField proc uses esi edi ebx loc:int_t, tokenarray:ptr asm_tok,
        name:string_t, mem_type:byte, vartype:ptr asym, size:uint_t

  local offs:int_32
  local len:int_t
  local s:ptr struct_info

    mov ecx,CurrStruct
    mov s,[ecx].dsym.structinfo
    mov offs,[ecx].asym.offs

    .if ( name )

        mov len,strlen( name )
        .if( eax > MAX_ID_LEN )
            asmerr(2043)
            .return( NULL )
        .endif
        SearchNameInStruct( CurrStruct, name, 0, 0 )
        .if ( eax )
            asmerr(2005, [eax].asym.name )
            .return( NULL )
        .endif
    .else
        ;; v2.06: check fields of anonymous struct member
        mov ecx,vartype
        .if ( ecx && \
            ( [ecx].asym.typekind == TYPE_STRUCT || \
              [ecx].asym.typekind == TYPE_UNION ) )
            CheckAnonymousStruct( ecx )
        .endif
        mov name,&@CStr("")
        mov len,0
    .endif
    mov ecx,loc
    .if ( ecx != -1 )

        mov  edi,StringBufferEnd
        inc  ecx
        imul ebx,ecx,asm_tok
        add  ebx,tokenarray

        .for ( : [ebx].token != T_FINAL : ebx += asm_tok )
            .if ( [ebx].token == T_ID )
                mov esi,SymSearch( [ebx].string_ptr )
                .if ( eax && [eax].asym.flags & S_VARIABLE )
                    .if ( [eax].asym.flags & S_PREDEFINED && [eax].asym.sfunc_ptr )
                        [eax].asym.sfunc_ptr( eax, NULL )
                        mov eax,esi
                    .endif
                    xor ecx,ecx
                    .ifs ( [eax].asym.value3264 < 0 )
                        inc ecx
                    .endif
                    mov edx,[eax].asym.uvalue
                    myltoa( edx, edi, ModuleInfo.radix, ecx, TRUE )
                    add edi,strlen( edi )
                    mov al,' '
                    stosb
                    .continue
                .endif
            .endif
            mov esi,[ebx].tokpos
            mov ecx,[ebx+16].tokpos
            sub ecx,esi
            rep movsb
        .endf
        mov byte ptr [edi],0
        mov ecx,edi
        sub ecx,StringBufferEnd
        mov esi,ecx
        add ecx,sizeof( sfield )
        mov edi,LclAlloc( ecx )
        xor eax,eax
        mov ecx,sizeof( sfield )
        mov edx,edi
        rep stosb
        lea edi,[edx].sfield.ivalue
        mov ecx,esi
        mov esi,StringBufferEnd
        inc ecx
        rep movsb
        mov edi,edx
    .else
        mov edi,LclAlloc( sizeof( sfield ) )
        xor eax,eax
        mov ecx,sizeof( sfield )
        mov edx,edi
        rep stosb
        mov edi,edx
    .endif

    ;; create the struct field symbol

    mov [edi].sym.name_size,len
    .if ( eax )
        mov [edi].sym.name,LclAlloc( &[eax+1] )
        mov esi,name
        mov ecx,len
        mov edx,edi
        mov edi,eax
        rep movsb
        mov byte ptr [edi],0
        mov edi,edx
    .else
        mov [edi].sym.name,&@CStr("")
    .endif
    mov [edi].sym.state,SYM_STRUCT_FIELD
    .if ( ModuleInfo.cref )
        or [edi].sym.flag1,S_LIST
    .endif
    or  [edi].sym.flags,S_ISDEFINED
    mov [edi].sym.mem_type,mem_type
    mov [edi].sym.type,vartype
    mov [edi].next,NULL

    mov esi,s
    .if ( [esi].head == NULL )
        mov [esi].head,edi
        mov [esi].tail,edi
    .else
        mov ecx,[esi].tail
        mov [ecx].sfield.next,edi
        mov [esi].tail,edi
    .endif

    ;; v2.0: for STRUCTs, don't use the struct's size for alignment calculations,
    ;; instead use the size of the "max" member!

    mov ecx,vartype
    .if ( mem_type == MT_TYPE && \
        ( [ecx].asym.typekind == TYPE_STRUCT || \
          [ecx].asym.typekind == TYPE_UNION ) )
        mov size,[ecx].asym.max_mbr_size
    .endif

    ;; align the field if an alignment argument was given

    movzx eax,[esi].alignment

    .if ( eax > 1 )

        ;; if it's the first field to add, use offset of the parent's current field

        mov ecx,size

        .if ( eax < ecx )

            lea ecx,[eax-1]
            mov edx,offs
            add edx,ecx
            neg eax
            and edx,eax
            mov offs,edx

        .elseif ( ecx )

            mov eax,ecx
            lea ecx,[eax-1]
            mov edx,offs
            add edx,ecx
            neg eax
            and edx,eax
            mov offs,edx

        .endif

        ;; adjust the struct's current offset + size.
        ;; The field's size is added in UpdateStructSize()

        mov ecx,CurrStruct
        .if ( [ecx].asym.typekind != TYPE_UNION )
            mov [ecx].asym.offs,offs
            .if ( offs > [ecx].asym.total_size )
                mov [ecx].asym.total_size,offs
            .endif
        .endif
    .endif
    mov ecx,CurrStruct
    .if ( size > [ecx].asym.max_mbr_size )
        mov [ecx].asym.max_mbr_size,size
    .endif
    mov [edi].sym.offs,offs

    ;; if -Zm is on, create a global symbol

    mov edx,name
    .if ( ModuleInfo.oldstructs == TRUE && byte ptr [edx] )
        SymLookup( name )
        .if ( [eax].asym.state == SYM_UNDEFINED )
            mov [eax].asym.state,SYM_STRUCT_FIELD
        .endif
        .if ( [eax].asym.state == SYM_STRUCT_FIELD )

            mov ecx,eax
            mov [ecx].asym.mem_type,mem_type
            mov [ecx].asym.type,vartype
            mov [ecx].asym.offs,offs ;; added v2.0

            ;; v2.01: must be the full offset.
            ;; (there's still a problem if alignment is > 1!)

            mov edx,CurrStruct
            .for ( edx = [edx].dsym.next : edx : edx = [edx].dsym.next )
                add [ecx].asym.offs,[edx].asym.offs
            .endf
            or [ecx].asym.flags,S_ISDEFINED
        .endif
    .endif
    .return( edi )

CreateStructField endp

;; called by AlignDirective() if ALIGN/EVEN has been found inside
;; a struct. It's already verified that <value> is a power of 2.

AlignInStruct proc value:int_t

    mov ecx,CurrStruct
    .if ( [ecx].asym.typekind != TYPE_UNION )

        mov eax,[ecx].asym.offs
        mov edx,value
        lea eax,[eax+edx-1]
        neg edx
        and eax,edx

        mov [ecx].asym.offs,eax
        .if ( eax > [ecx].asym.total_size )
            mov [ecx].asym.total_size,eax
        .endif
    .endif
    .return( NOT_ERROR )

AlignInStruct endp

;; called by data_dir() when a structure field has been created.


UpdateStructSize proc sym:ptr asym

    mov edx,sym
    mov ecx,CurrStruct
    .if ( [ecx].asym.typekind == TYPE_UNION )
        .if ( [edx].asym.total_size > [ecx].asym.total_size )
            mov [ecx].asym.total_size,[edx].asym.total_size
        .endif
    .else
        add [ecx].asym.offs,[edx].asym.total_size
        .ifs ( [ecx].asym.offs > [ecx].asym.total_size )
            mov [ecx].asym.total_size,[ecx].asym.offs
        .endif
    .endif
    ret
UpdateStructSize endp

;; called if ORG occurs inside STRUCT/UNION definition

SetStructCurrentOffset proc offs:int_t

    mov ecx,CurrStruct
    .if ( [ecx].asym.typekind == TYPE_UNION )
        .return( asmerr( 2200 ) )
    .endif
    mov [ecx].asym.offs,offs
    ;; if an ORG is inside the struct, it cannot be instanced anymore
    mov edx,[ecx].dsym.structinfo
    or [edx].struct_info.flags,SI_ORGINSIDE
    .ifs ( offs > [ecx].asym.total_size )
        mov [ecx].asym.total_size,offs
    .endif
    .return( NOT_ERROR )

SetStructCurrentOffset endp

;; get a qualified type.
;; Used by
;; - TYPEDEF
;; - PROC/PROTO params and LOCALs
;; - EXTERNDEF
;; - EXTERN
;; - LABEL
;; - ASSUME for GPRs

    assume esi:ptr qualified_type
    assume edi:nothing

GetQualifiedType proc uses esi edi ebx pi:ptr int_t, tokenarray:ptr asm_tok,
        pti:ptr qualified_type

    mov ecx,pi
   .new type:int_t
   .new tmp:int_t
   .new mem_type:byte
   .new i:int_t = [ecx]
   .new distance:int_t = FALSE

    imul ebx,i,asm_tok
    add  ebx,tokenarray
    mov  edx,ebx

    ;; convert PROC token to a type qualifier

    .for ( : [ebx].token != T_FINAL && [ebx].token != T_COMMA : ebx += asm_tok )
        .if ( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_PROC )
            mov [ebx].token,T_STYPE
            ;; v2.06: avoid to use ST_PROC
            mov cl,ModuleInfo._model
            mov eax,1
            shl eax,cl
            and eax,SIZE_CODEPTR
            mov ecx,T_NEAR
            .ifnz
                mov ecx,T_FAR
            .endif
            mov [ebx].tokval,ecx
        .endif
    .endf
    mov ebx,edx

    ;; with NEAR/FAR, there are several syntax variants allowed:
    ;; 1. NEARxx | FARxx
    ;; 2. PTR NEARxx | FARxx
    ;; 3. NEARxx | FARxx PTR [<type>]

    ;; read qualified type

    mov esi,pti
    .for ( type = ERROR : [ebx].token == T_STYPE || [ebx].token == T_BINARY_OPERATOR : ebx += asm_tok )
        .if ( [ebx].token == T_STYPE )
            mov edi,[ebx].tokval
            .if ( type == ERROR )
                mov type,edi
            .endif
            mov mem_type,GetMemtypeSp( edi )
            .if ( al == MT_FAR || al == MT_NEAR )
                .if ( distance == FALSE )
                    mov eax,GetSflagsSp( edi )
                    cmp mem_type,MT_FAR
                    setz cl
                    mov [esi].is_far,cl
                    .if ( eax != USE_EMPTY )
                        mov [esi].Ofssize,al
                    .endif
                    mov distance,TRUE
                .elseif ( [ebx-16].tokval != T_PTR )
                    .break
                .endif
            .else
                .if ( [esi].is_ptr )
                    mov [esi].ptr_memtype,mem_type
                .endif
                add ebx,asm_tok
                .break
            .endif
        .elseif ( [ebx].tokval == T_PTR )
            mov type,EMPTY
            inc [esi].is_ptr
        .else
            .break
        .endif
    .endf

    .if ( type == EMPTY )
        .if ( [ebx].token == T_ID && [ebx-16].tokval == T_PTR )
            mov [esi].symtype,SymSearch( [ebx].string_ptr )
            mov edi,[esi].symtype
            .if ( edi == NULL || [edi].asym.state == SYM_UNDEFINED )
                mov [esi].symtype,CreateTypeSymbol( edi, [ebx].string_ptr, TRUE )
            .elseif ( [edi].asym.state != SYM_TYPE )
                .return( asmerr( 2004, [ebx].string_ptr ) )
            .else
                ;; if it's a typedef, simplify the info
                .if ( [edi].asym.typekind == TYPE_TYPEDEF )
                    add [esi].is_ptr,[edi].asym.is_ptr
                    .if ( [edi].asym.is_ptr == 0 )
                        mov al,MT_EMPTY
                        .if ( [edi].asym.mem_type != MT_TYPE )
                            mov al,[edi].asym.mem_type
                        .endif
                        mov [esi].ptr_memtype,al
                        .if ( distance == FALSE && [esi].is_ptr == 1 && \
                            ( [edi].asym.mem_type == MT_NEAR || \
                              [edi].asym.mem_type == MT_PROC || \
                              [edi].asym.mem_type == MT_FAR ) )

                            mov [esi].is_far,0
                            .if ( [edi].asym.sflags & S_ISFAR )
                                mov [esi].is_far,1
                            .endif
                            .if ( [edi].asym.Ofssize != USE_EMPTY )
                                mov [esi].Ofssize,[edi].asym.Ofssize
                            .endif
                        .endif
                    .else
                        mov [esi].ptr_memtype,[edi].asym.ptr_memtype
                        .if ( distance == FALSE && [esi].is_ptr == 1 )
                            mov [esi].is_far,0
                            .if ( [edi].asym.sflags & S_ISFAR )
                                mov [esi].is_far,1
                            .endif
                            .if ( [edi].asym.Ofssize != USE_EMPTY )
                                mov [esi].Ofssize,[edi].asym.Ofssize
                            .endif
                        .endif
                    .endif
                    .if ( [edi].asym.mem_type == MT_TYPE )
                        mov [esi].symtype,[edi].asym.type
                    .else
                        mov [esi].symtype,[edi].asym.target_type
                    .endif
                .endif
            .endif
            add ebx,asm_tok
        .endif
    .endif

    .if ( type == ERROR )
        .if ( [ebx].token != T_ID )
            .if ( [ebx].token == T_FINAL || [ebx].token == T_COMMA )
                asmerr( 2175 )
            .else
                asmerr( 2008, [ebx].string_ptr )
                ;add ebx,asm_tok
            .endif
            .return( ERROR )
        .endif
        mov [esi].symtype,SymSearch( [ebx].string_ptr )
        mov edi,eax
        .if ( edi == NULL || [edi].asym.state != SYM_TYPE )
            .if ( [esi].symtype == NULL || [edi].asym.state == SYM_UNDEFINED )
                asmerr( 2006, [ebx].string_ptr )
            .else
                asmerr( 2004, [ebx].string_ptr )
            .endif
            .return( ERROR )
        .endif
        mov edi,[esi].symtype
        .if ( [edi].asym.typekind == TYPE_TYPEDEF )
            mov [esi].mem_type,[edi].asym.mem_type
            mov [esi].is_far,0
            .if ( [edi].asym.sflags & S_ISFAR )
                mov [esi].is_far,1
            .endif
            mov [esi].is_ptr,[edi].asym.is_ptr
            mov [esi].Ofssize,[edi].asym.Ofssize
            mov [esi].size,[edi].asym.total_size
            mov [esi].ptr_memtype,[edi].asym.ptr_memtype
            .if ( [edi].asym.mem_type == MT_TYPE )
                mov [esi].symtype,[edi].asym.type
            .else
                mov [esi].symtype,[edi].asym.target_type
            .endif

        .else
            mov [esi].mem_type,MT_TYPE
            mov [esi].size,[edi].asym.total_size
        .endif
        add ebx,asm_tok
    .else
        .if ( [esi].is_ptr )
            mov [esi].mem_type,MT_PTR
        .else
            mov [esi].mem_type,GetMemtypeSp( type )
        .endif
        .if ( [esi].mem_type == MT_PTR )
            mov ecx,MT_NEAR
            .if ([esi].is_far )
                mov ecx,MT_FAR
            .endif
            mov [esi].size,SizeFromMemtype( cl, [esi].Ofssize, NULL )
        .else
            mov [esi].size,SizeFromMemtype( [esi].mem_type, [esi].Ofssize, NULL )
        .endif
    .endif
    mov ecx,pi
    mov eax,ebx
    sub eax,tokenarray
    shr eax,4
    mov [ecx],eax
    .return( NOT_ERROR )
GetQualifiedType endp

;; TYPEDEF directive. Syntax is:
;; <type name> TYPEDEF [proto|[far|near [ptr]]<qualified type>]

CreateType proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok, name:string_t, pp:ptr asym

  local ti:qualified_type

    mov edi,SymSearch( name )
    .if ( edi == NULL || [edi].asym.state == SYM_UNDEFINED )
        mov edi,CreateTypeSymbol( edi, name, TRUE )
        .if ( edi == NULL )
            .return( ERROR )
        .endif
if TYPEOPT
        ;; release the structinfo data extension
        mov [edi].dsym.structinfo,NULL
endif
    .else
        ;; MASM allows to have the TYPEDEF included multiple times
        ;; but the types must be identical!
        .if ( ( [edi].asym.state != SYM_TYPE ) || \
              ( [edi].asym.typekind != TYPE_TYPEDEF && \
                [edi].asym.typekind != TYPE_NONE ) )
            .return( asmerr( 2005, [edi].asym.name ) )
        .endif
    .endif
    mov ecx,pp
    .if ( ecx )
        mov [ecx],edi
    .endif

    or [edi].asym.flags,S_ISDEFINED
    .if ( ecx == NULL && Parse_Pass > PASS_1 )
        .return( NOT_ERROR )
    .endif
    mov [edi].asym.typekind,TYPE_TYPEDEF
    imul ebx,i,asm_tok
    add  ebx,tokenarray

    ;; PROTO is special
    .if ( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_PROTO )

        ;; v2.04: added check if prototype is set already
        .if ( [edi].asym.target_type == NULL && [edi].asym.mem_type == MT_EMPTY )
            CreateProc( NULL, "", SYM_TYPE )
        .elseif ( [edi].asym.mem_type == MT_PROC )
            mov eax,[edi].asym.target_type
        .else
            .return( asmerr( 2004, [edi].asym.name ) )
        .endif
        inc i
        mov esi,eax
        .return .if ( ParseProc( esi, i, tokenarray, FALSE, ModuleInfo.langtype ) == ERROR )

        assume esi:nothing
        mov [edi].asym.mem_type,MT_PROC
        mov al,[esi].asym.sflags
        and al,S_SEGOFSSIZE
        mov [edi].asym.Ofssize,al
        ;; v2.03: set value of field total_size (previously was 0)
        mov eax,2
        mov cl,[edi].asym.Ofssize
        shl eax,cl
        mov [edi].asym.total_size,eax
        .if ( [esi].asym.mem_type != MT_NEAR )
            or  [edi].asym.sflags,S_ISFAR ;; v2.04: added
            add [edi].asym.total_size,2
        .endif
        mov [edi].asym.target_type,esi
        .return( NOT_ERROR )
    .endif

    mov ti.size,0
    mov ti.is_ptr,0
    mov ti.is_far,FALSE
    mov ti.mem_type,MT_EMPTY
    mov ti.ptr_memtype,MT_EMPTY
    mov ti.symtype,NULL
    mov ti.Ofssize,ModuleInfo.Ofssize

    ;; "empty" type is ok for TYPEDEF
    .if ( [ebx].token == T_FINAL || [ebx].token == T_COMMA )
        ;
    .elseif ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
        .return
    .endif

    ;; if type did exist already, check for type conflicts
    ;; v2.05: this code has been rewritten

    .if ( [edi].asym.mem_type != MT_EMPTY )

        .for( ecx = ti.symtype : ecx && [ecx].asym.type : ecx = [ecx].asym.type )
        .endf
        mov edx,[edi].asym.target_type
        .if ( [edi].asym.mem_type == MT_TYPE )
            mov edx,[edi].asym.type
        .endif
        .for( : edx && [edx].asym.type : edx = [edx].asym.type )
        .endf
        mov bl,ModuleInfo.Ofssize
        mov bh,bl
        .if ( [edi].asym.Ofssize != USE_EMPTY )
            mov bl,[edi].asym.Ofssize
        .endif
        .if ( ti.Ofssize != USE_EMPTY )
            mov bh,ti.Ofssize
        .endif
        cmp bl,bl
        setnz bl
        test [edi].asym.sflags,S_ISFAR
        setnz bh
        .if ( ti.mem_type != [edi].asym.mem_type || \
            ( ti.mem_type == MT_TYPE && ecx != edx ) || \
            ( ti.mem_type == MT_PTR && \
            ( ti.is_far != bh || bl || \
              ti.ptr_memtype != [edi].asym.ptr_memtype || \
              ecx != edx ) ) )
            .return( asmerr( 2004, name ) )
        .endif
    .endif

    mov [edi].asym.mem_type,ti.mem_type
    mov [edi].asym.Ofssize,ti.Ofssize
    mov [edi].asym.total_size,ti.size
    mov [edi].asym.is_ptr,ti.is_ptr
    .if ( ti.is_far )
        or [edi].asym.sflags,S_ISFAR
    .endif
    .if ( ti.mem_type == MT_TYPE )
        mov [edi].asym.type,ti.symtype
    .else
        mov [edi].asym.target_type,ti.symtype
    .endif
    mov [edi].asym.ptr_memtype,ti.ptr_memtype
    imul ebx,i,asm_tok
    add  ebx,tokenarray

    .if ( pp == NULL && [ebx].token != T_FINAL )
        .return( asmerr(2008, [ebx].string_ptr ) )
    .endif
    .return( NOT_ERROR )
CreateType endp

TypedefDirective proc uses ebx i:int_t, tokenarray:ptr asm_tok

    imul ebx,i,asm_tok
    add  ebx,tokenarray
    .if( i != 1 )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif
    inc i
    mov ebx,tokenarray
    .return( CreateType( i, ebx, [ebx].string_ptr, NULL ) )
TypedefDirective endp

;; RECORD directive
;; syntax: <label> RECORD <bitfield_name>:<size>[,...]
;; defines a RECORD type (state=SYM_TYPE).
;; the memtype will be MT_BYTE, MT_WORD, MT_DWORD [, MT_QWORD in 64-bit].

RecordDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

   .new name:string_t
   .new newr:ptr dsym
   .new oldr:ptr dsym = NULL
   .new cntBits:int_t
   .new def:int_t
   .new len:int_t
   .new redef_err:int_t
   .new count:int_t
   .new init_loc:ptr asm_tok
   .new opndx:expr
   .new offs:uint_t

    mov ebx,tokenarray
    mov name,[ebx].string_ptr
    imul ecx,i,asm_tok
    add ebx,ecx

    .if ( i != 1 )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif
    mov esi,SymSearch( name )

    .if ( esi == NULL || [esi].asym.state == SYM_UNDEFINED )
        mov esi,CreateTypeSymbol( esi, name, TRUE )
    .elseif ( [esi].asym.state == SYM_TYPE && \
            ( [esi].asym.typekind == TYPE_RECORD || \
              [esi].asym.typekind == TYPE_NONE ) )

        ;; v2.04: allow redefinition of record and forward references.
        ;; the record redefinition may have different initial values,
        ;; but those new values are IGNORED! ( Masm bug? )

        .if ( Parse_Pass == PASS_1 && [esi].asym.typekind == TYPE_RECORD )
            mov oldr,esi
            mov esi,CreateTypeSymbol( NULL, name, FALSE )
            mov redef_err,0
        .endif
    .else
        .return( asmerr( 2005, name ) )
    .endif
    or [esi].asym.flags,S_ISDEFINED

    .if ( Parse_Pass > PASS_1 )
        .return( NOT_ERROR )
    .endif

    mov newr,esi
    mov [esi].asym.typekind,TYPE_RECORD

    inc i ;; go past RECORD
    add ebx,asm_tok

    mov cntBits,0 ;; counter for total of bits in record
    ;; parse bitfields
    .repeat
        .if ( [ebx].token != T_ID )
            asmerr( 2008, [ebx].string_ptr )
            .break
        .endif
        mov len,strlen( [ebx].string_ptr )
        .if ( eax > MAX_ID_LEN )
            asmerr( 2043 )
            .break
        .endif
        mov edi,ebx
        inc i
        .if ( [ebx+16].token != T_COLON )
            asmerr( 2065, "" )
            .break
        .endif
        inc i
        ;; get width
        .break .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )

        .if ( opndx.kind != EXPR_CONST )
            asmerr( 2026 )
            mov opndx.value,1
        .endif

        mov ecx,opndx.value
        add ecx,cntBits
        mov eax,32
        .if ( ModuleInfo.Ofssize == USE64 )
            mov eax,64
        .endif
        .if ( opndx.value == 0 )
            asmerr( 2172, [ebx].string_ptr )
            .break
        .elseif ( ecx > eax )
            asmerr( 2089, [ebx].string_ptr )
            .break
        .endif
        mov count,0

        ;; is there an initializer? ('=')

        imul ebx,i,asm_tok
        add ebx,tokenarray
        .if ( [ebx].token == T_DIRECTIVE && [ebx].dirtype == DRT_EQUALSGN )
            inc i
            add ebx,asm_tok
            mov ecx,ebx
            mov init_loc,ebx
            .for( : [ebx].token != T_FINAL && [ebx].token != T_COMMA: i++, ebx += asm_tok )
            .endf
            ;; no value?
            .if ( ecx == ebx )
                asmerr( 2008, [edi].asm_tok.tokpos )
                .break
            .endif
            ;; v2.09: initial values of record redefinitions are ignored!
            .if ( oldr == NULL )
                mov eax,[ebx].tokpos
                sub eax,[ecx].asm_tok.tokpos
                mov count,eax
            .endif
        .endif

        ;; record field names are global! (Masm design flaw)

        mov esi,SymSearch( [edi].asm_tok.string_ptr )
        mov def,TRUE
        .if ( oldr )
            .if ( esi == NULL || \
                [esi].asym.state != SYM_STRUCT_FIELD || \
                [esi].asym.mem_type != MT_BITS || \
                [esi].asym.total_size != opndx.value )
                asmerr( 2007, szRecord, [edi].asm_tok.string_ptr )
                inc redef_err
                mov def,FALSE ;; v2.06: added
            .endif
        .else
            .if ( esi )
                asmerr( 2005, [esi].asym.name )
                .break
            .endif
        .endif

        .if ( def ) ;; v2.06: don't add field if there was an error

            mov esi,[edi].asm_tok.string_ptr
            add cntBits,opndx.value
            mov ecx,count
            mov edx,LclAlloc( &[ecx+sizeof( sfield )] )
            mov ecx,sizeof( sfield )
            mov edi,eax
            xor eax,eax
            rep stosb
            mov edi,edx
            assume edi:ptr sfield

            mov ecx,len
            mov [edi].sym.name_size,cx
            inc ecx
            mov [edi].sym.name,LclAlloc( ecx )

            mov edx,edi
            mov edi,eax
            mov ecx,len
            inc ecx
            rep movsb
            mov edi,edx

            and [edi].sym.flag1,not S_LIST
            mov al,ModuleInfo.cref
            or  [edi].sym.flag1,al
            mov [edi].sym.state,SYM_STRUCT_FIELD
            mov [edi].sym.mem_type,MT_BITS
            mov [edi].sym.total_size,opndx.value
            .if ( !oldr )
                SymAddGlobal( edi )
            .endif
            mov [edi].next,NULL
            mov [edi].ivalue[0],0
            mov ecx,newr
            mov ecx,[ecx].dsym.structinfo
            .if ( [ecx].struct_info.head == NULL )
                mov [ecx].struct_info.head,edi
                mov [ecx].struct_info.tail,edi
            .else
                mov edx,[ecx].struct_info.tail
                mov [edx].sfield.next,edi
                mov [ecx].struct_info.tail,edi
            .endif
            .if ( count )
                mov ecx,init_loc
                mov edx,edi
                mov esi,[ecx].asm_tok.tokpos
                lea edi,[edi].ivalue
                mov ecx,count
                rep movsb
                mov byte ptr [edi],0
                mov edi,edx
            .endif
        .endif

        .if ( i < Token_Count )
            .if ( [ebx].token != T_COMMA || [ebx+16].token == T_FINAL )
                asmerr(2008, [ebx].tokpos )
                .break
            .endif
            inc i
            add ebx,asm_tok
        .endif

    .until ( i >= Token_Count )

    ;; now calc size in bytes and set the bit positions
    mov esi,newr
    mov eax,cntBits
    .if ( eax > 16 )
        .if ( eax > 32 )
            mov [esi].asym.total_size,QWORD
            mov [esi].asym.mem_type,MT_QWORD
        .else
            mov [esi].asym.total_size,DWORD
            mov [esi].asym.mem_type,MT_DWORD
        .endif
    .elseif ( eax > 8 )
        mov [esi].asym.total_size,WORD
        mov [esi].asym.mem_type,MT_WORD
    .else
        mov [esi].asym.total_size,BYTE
        mov [esi].asym.mem_type,MT_BYTE
    .endif

    ;; if the BYTE/WORD/DWORD isn't used fully, shift bits to the right!
    ;; set the bit position
    mov ecx,[esi].dsym.structinfo
    .for ( edi = [ecx].struct_info.head: edi: edi = [edi].next )
        sub eax,[edi].sym.total_size
        mov [edi].sym.offs,eax
    .endf
    .if ( oldr )
        .if ( redef_err > 0 || \
            AreStructsEqual( newr, oldr ) == FALSE )
            asmerr( 2007, szRecord, [esi].asym.name )
        .endif

        ;; record can be freed, because the record's fields are global items.
        ;; And initial values of the new definition are ignored!

        SymFree( newr )
    .endif
    .return( NOT_ERROR )
RecordDirective endp

    end
