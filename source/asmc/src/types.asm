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

; text constants for 'Non-benign <x> redefinition' error msg

define szStructure <"structure">
define szRecord <"record">

define szNonUnique <"NONUNIQUE">

.code

TypesInit proc

    mov CurrStruct,NULL
    mov redef_struct,NULL
    ret

TypesInit endp

; create a SYM_TYPE symbol.
; <sym> must be NULL or of state SYM_UNDEFINED.
; <name> and <global> are only used if <sym> is NULL.
; <name> might be an empty string.

CreateTypeSymbol proc __ccall uses rsi rdi sym:ptr asym, name:string_t, global:int_t

    ldr rsi,sym
    .if ( rsi )
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rsi )
    .else
        .if ( global )
            SymCreate( name )
        .else
            SymAlloc( name )
        .endif
        mov rsi,rax
    .endif

    .if ( rsi )

        mov [rsi].asym.state,SYM_TYPE
        mov [rsi].asym.typekind,TYPE_NONE
        mov rdi,LclAlloc( sizeof( struct_info ) )
        mov [rsi].dsym.structinfo,rdi
        mov [rdi].struct_info.head,NULL
        mov [rdi].struct_info.tail,NULL
        mov [rdi].struct_info.alignment,0
        mov [rdi].struct_info.flags,0
    .endif
    .return( rsi )

CreateTypeSymbol endp


; search a name in a struct's fieldlist

    assume rbx:ptr sfield

SearchNameInStruct proc __ccall uses rsi rdi rbx tstruct:ptr asym, name:string_t,
        poffset:ptr uint_32, level:int_t

    mov edi,tstrlen( name )
    xor esi,esi

    mov rcx,tstruct
    mov rdx,[rcx].dsym.structinfo
    mov rbx,[rdx].struct_info.head

    .if ( level >= MAX_STRUCT_NESTING )

        asmerr( 1007 )
       .return( NULL )
    .endif

    inc level

    .for ( : rbx : rbx = [rbx].next )

        ; recursion: if member has no name, check if it is a structure
        ; and scan this structure's fieldlist then

        mov rax,[rbx].name
        .if ( byte ptr [rax] == 0 )

            ; there are 2 cases: an anonymous inline struct ...

            .if ( [rbx].state == SYM_TYPE )
                .if ( SearchNameInStruct( rbx, name, poffset, level ) )
                    mov rsi,rax
                    mov rcx,poffset
                    .if rcx
                        add [rcx],[rbx].offs
                    .endif
                    .break
                .endif

            ; or an anonymous structured field

            .elseif ( [rbx].mem_type == MT_TYPE )
                .if ( SearchNameInStruct( [rbx].type, name, poffset, level ) )
                    mov rsi,rax
                    mov rcx,poffset
                    .if rcx
                        add [rcx],[rbx].offs
                    .endif
                    .break
                .endif
            .endif
        .elseif ( edi == [rbx].name_size )
            .if ( SymCmpFunc( name, [rbx].name, edi ) == 0 )
                mov rsi,rbx
               .break
            .endif
        .endif
    .endf
    .return( rsi )

SearchNameInStruct endp

; check if a struct has changed

    assume rdi:ptr sfield

AreStructsEqual proc __ccall private uses rdi rbx newstr:ptr dsym, oldstr:ptr dsym

    ldr rcx,newstr
    ldr rdx,oldstr

    mov rax,[rdx].dsym.structinfo
    mov rbx,[rax].struct_info.head
    mov rcx,[rcx].dsym.structinfo
    mov rdi,[rcx].struct_info.head

    ; kind of structs must be identical
    .if ( [rbx].typekind != [rdi].typekind )
        .return( FALSE )
    .endif

    .for ( : rbx : rbx = [rbx].next, rdi = [rdi].next )
        .if ( !rdi )
            .return( FALSE )
        .endif
        ; for global member names, don't check the name if it's ""
        mov rax,[rdi].name

        .if ( MODULE.oldstructs && byte ptr [rax] == 0 )
            ;
        .elseifd ( tstrcmp( [rbx].name, [rdi].name ) )
            .return( FALSE )
        .endif
        .if ( [rbx].offs != [rdi].offs )
            .return( FALSE )
        .endif
        .if ( [rbx].total_size != [rdi].total_size )
            .return( FALSE )
        .endif
    .endf
    .if ( rdi )
        .return( FALSE )
    .endif
    .return( TRUE )

AreStructsEqual endp


; handle STRUCT, STRUC, UNION directives
; i = index of directive token

    assume rbx:ptr asm_tok
    assume rdi:nothing

StructDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local alignment:uint_t
  local offs:uint_t
  local typekind:byte

    ; top level structs/unions must have an identifier at pos 0.
    ; for embedded structs, the directive must be at pos 0,
    ; an identifier is optional then.

    ldr ecx,i
    ldr rbx,tokenarray
    mov rsi,[rbx].string_ptr
    imul ecx,ecx,asm_tok
    add rbx,rcx

    mov al,TYPE_STRUCT
    .if ( [rbx].tokval == T_UNION )
        mov al,TYPE_UNION
    .elseif ( [rbx].tokval == T_RECORD )
        mov al,TYPE_RECORD
    .endif
    mov typekind,al

    mov rax,CurrStruct
    .if ( ( rax == NULL && i != 1 ) || ( rax != NULL && i != 0 ) )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif

    mov eax,1
    mov cl,MODULE.fieldalign
    shl eax,cl
    mov alignment,eax

    inc i ; go past STRUCT/UNION
    add rbx,asm_tok

    .if ( i == 1 ) ; embedded struct?

        ; scan for the optional name

        lea rsi,@CStr("")
if ANYNAME
        ; the name might be a reserved word!
        ; Masm won't allow those.
else
        .if ( [rbx].token == T_ID )
endif
            mov rsi,[rbx].string_ptr
            inc i
            add rbx,asm_tok
        .endif
    .endif

    ; get an optional alignment argument: 1,2,4,8,16 or 32

    .if ( CurrStruct == NULL && [rbx].token != T_FINAL )

        .new opndx:expr

        ; get the optional alignment parameter.
        ; forward references aren't accepted, but EXPF_NOUNDEF isn't used here!

        .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) != ERROR )

            ; an empty expression is accepted

            mov rcx,opndx.sym
            .if ( opndx.kind == EXPR_EMPTY )

            .elseif ( opndx.kind != EXPR_CONST )

                ; v2.09: better error msg

                .if ( rcx && [rcx].asym.state == SYM_UNDEFINED )
                    asmerr( 2006, [rcx].asym.name )
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
        add rbx,tokenarray

        ; there might also be the NONUNIQUE parameter

        .if ( [rbx].token == T_COMMA )
            inc i
            add rbx,asm_tok
            .if ( [rbx].token == T_ID )
                .ifd ( tstricmp( [rbx].string_ptr, szNonUnique ) == 0 )

                    ; currently NONUNIQUE is ignored

                    asmerr( 8017, szNonUnique )
                    inc i
                    add rbx,asm_tok
                .endif
            .endif
        .endif
    .endif
    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].tokpos ) )
    .endif

    ; does struct have a name?

    .if ( byte ptr [rsi] )
        .if ( CurrStruct == NULL )

            ; the "top-level" struct is part of the global namespace

            mov rdi,SymSearch( rsi )
        .else
            mov rdi,SearchNameInStruct( CurrStruct, rsi, &offs, 0 )
        .endif
    .else
        mov edi,NULL ; anonymous struct
    .endif

    .if ( MODULE.list )
        mov rcx,CurrStruct
        .if ( rcx )
            LstWrite( LSTTYPE_STRUCT, [rcx].asym.total_size, NULL )
        .else
            LstWrite( LSTTYPE_STRUCT, 0, NULL )
        .endif
    .endif

    ; if pass is > 1, update struct stack + CurrStruct.offset and exit
    .if ( Parse_Pass > PASS_1 )

        ; v2.04 changed. the previous implementation was insecure.
        ; See also change in data.c, behind CreateStructField().

        mov rcx,CurrStruct
        .if ( rcx )
            mov rcx,[rcx].dsym.structinfo
            mov rdx,[rcx].struct_info.tail
            mov rdi,[rdx].sfield.type
            mov [rcx].struct_info.tail,[rdx].sfield.next
        .endif
        mov rcx,[rdi].dsym.structinfo
        mov rax,[rcx].struct_info.head
        mov [rcx].struct_info.tail,rax
        mov [rdi].asym.offs,0
        or  [rdi].asym.flags,S_ISDEFINED
        mov [rdi].asym.state,SYM_TYPE ; added v2.33.68
        mov [rdi].dsym.next,CurrStruct
        mov CurrStruct,rdi
       .return( NOT_ERROR )
    .endif

    .if ( rdi == NULL )

        ; embedded or global STRUCT?

        .if ( CurrStruct == NULL )
            mov rdi,CreateTypeSymbol( NULL, rsi, TRUE )
        .else

            ; an embedded struct is split in an anonymous STRUCT type
            ; and a struct field with/without name

            mov rdi,CreateTypeSymbol( NULL, rsi, FALSE )

            ; v2: don't create the struct field here. First the
            ; structure must be read in ( because of alignment issues

            mov rcx,CurrStruct
            mov rcx,[rcx].dsym.structinfo

            mov alignment,[rcx].struct_info.alignment
        .endif

    .elseif ( [rdi].asym.state == SYM_UNDEFINED )

        ; forward reference

        xor eax,eax
        .if ( CurrStruct == NULL )
            inc eax
        .endif
        CreateTypeSymbol( rdi, NULL, eax )

    .elseif ( [rdi].asym.state == SYM_TYPE && CurrStruct == NULL )

        .switch ( [rdi].asym.typekind )
        .case TYPE_STRUCT
        .case TYPE_UNION

            ; if a struct is redefined as a union ( or vice versa )
            ; do accept the directive and just check if the redefinition
            ; is compatible (usually it isn't)

            mov redef_struct,rdi
            mov rdi,CreateTypeSymbol( NULL, rsi, FALSE )
            .endc
        .case TYPE_NONE ; TYPE_NONE is forward reference
            .endc
        .default
            .return( asmerr( 2005, [rdi].asym.name ) )
        .endsw

    .else
        .return( asmerr( 2005, [rdi].asym.name ) )
    .endif

    mov [rdi].asym.offs,0
    mov [rdi].asym.typekind,typekind

    mov rcx,[rdi].dsym.structinfo
    mov [rcx].struct_info.alignment,alignment
    or [rcx].struct_info.flags,SI_ISOPEN
    .if ( CurrStruct )
        or [rcx].struct_info.flags,SI_ISINLINE
    .endif

    mov [rdi].dsym.next,CurrStruct

    .if ( MODULE.ComStack )

        mov rbx,MODULE.ComStack
        assume rbx:ptr com_item

        mov  ecx,tstrlen( [rbx].class )
        mov  rdx,rdi
        mov  rdi,[rbx].class
        repz cmpsb
        mov  rdi,rdx
        .ifz
            mov eax,[rsi]
            .if ( al == 0 )
                mov [rbx].sym,rdi
                or  [rdi].asym.flags,S_CLASS
            .elseif ( eax == 'lbtV' && byte ptr [rsi+4] == 0 )
                mov rcx,[rbx].sym
                or  [rcx].asym.flags,S_VTABLE
                mov [rcx].asym.vtable,rdi
                mov [rdi].asym.class,rcx
                or  [rdi].asym.flags,S_ISVTABLE
            .endif
        .endif
        assume rbx:ptr asm_tok
    .endif
    mov CurrStruct,rdi

    .return( NOT_ERROR )

StructDirective endp


; handle ENDS directive when a struct/union definition is active

EndstructDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

    mov rdi,CurrStruct ; cannot be NULL

    ; if pass is > 1 just do minimal work

    .if ( Parse_Pass > PASS_1 )

        mov [rdi].asym.offs,0
        mov ebx,[rdi].asym.total_size
        mov CurrStruct,[rdi].dsym.next
        .if ( CurrStruct )
            UpdateStructSize( rdi )
        .endif
        .if ( CurrFile[LST*size_t] )
            LstWrite( LSTTYPE_STRUCT, ebx, rdi )
        .endif
        .return( NOT_ERROR )
    .endif

    ; syntax is either "<name> ENDS" (i=1) or "ENDS" (i=0).
    ; first case must be top level (next=NULL), latter case must NOT be top level (next!=NULL)

    mov rbx,tokenarray
    .if ( ( i == 1 && [rdi].dsym.next == NULL ) ||
          ( i == 0 && [rdi].dsym.next != NULL ) )

    .else
        lea rdx,@CStr("")
        .if ( i == 1 )
            mov rdx,[rbx].asm_tok.string_ptr
        .endif
        .return( asmerr( 1010, rdx ) )
    .endif

    .if ( i == 1 ) ; an global struct ends with <name ENDS>
        .if ( SymCmpFunc( [rbx].string_ptr, [rdi].asym.name, [rdi].asym.name_size ) != 0 )

            ; names don't match

            .return( asmerr( 1010, [rbx].string_ptr ) )
        .endif
    .endif

    inc i ; go past ENDS
    imul ecx,i,asm_tok
    add rbx,rcx

    ; v2.07: if ORG was used inside the struct, the struct's size
    ; has to be calculated now - there may exist negative offsets.

    mov rsi,[rdi].dsym.structinfo

    .if ( [rsi].struct_info.flags & SI_ORGINSIDE )

        .for ( ecx = 0, rdx = [rsi].struct_info.head: rdx: rdx = [rdx].sfield.next )

            .if ( [rdx].sfield.offs < ecx )
                mov ecx,[rdx].sfield.offs
            .endif
        .endf

        mov eax,[rdi].asym.total_size
        sub eax,ecx
        mov [rdi].asym.total_size,eax
    .endif

    ; Pad bytes at the end of the structure.

    ; v2.02: this is to be done in any case, whether -Zg is set or not

    movzx edx,[rsi].struct_info.alignment
    .if ( edx > 1 )
        mov eax,[rdi].asym.max_mbr_size
        .if ( eax == 0 )
            inc eax
        .endif
        .if ( eax > edx )
            mov eax,edx
        .endif
        mov ecx,eax
        neg ecx
        add eax,[rdi].asym.total_size
        dec eax
        and eax,ecx
        mov [rdi].asym.total_size,eax
    .endif

    and [rsi].struct_info.flags,not SI_ISOPEN
    or  [rdi].asym.flags,S_ISDEFINED

    ; if there's a negative offset, size will be wrong!

    mov esi,[rdi].asym.total_size

    ; reset offset, it's just used during the definition

    mov [rdi].asym.offs,0

    mov CurrStruct,[rdi].dsym.next
    .if ( i == 1 )

        mov rcx,[rdi].asym.name
        .if ( byte ptr [rcx] == 0 )
            xor ecx,ecx
        .endif
        CreateStructField( -1, NULL, rcx, MT_TYPE, rdi, [rdi].asym.total_size )
        mov ecx,[rdi].asym.total_size
        mov [rax].asym.total_size,ecx
        mov [rdi].asym.name,&@CStr("") ; the type becomes anonymous
        mov [rdi].asym.name_size,0
    .endif

    .if ( CurrFile[LST*size_t] )
        LstWrite( LSTTYPE_STRUCT, si, rdi )
    .endif

    ;
    ; to allow direct structure access
    ;
    .if ( [rdi].asym.sflags & S_ISVECTOR )

        movzx eax,[rdi].asym.regist[2]
        mov [rdi].asym.mem_type,GetMemtypeSp(eax)
    .else
        mov eax,[rdi].asym.total_size
        .switch ( eax )
        .case 1:  mov [rdi].asym.mem_type,MT_BYTE   : .endc
        .case 2:  mov [rdi].asym.mem_type,MT_WORD   : .endc
        .case 4:  mov [rdi].asym.mem_type,MT_DWORD  : .endc
        .case 6:  mov [rdi].asym.mem_type,MT_FWORD  : .endc
        .case 8:  mov [rdi].asym.mem_type,MT_QWORD  : .endc
        .default
            mov [rdi].asym.mem_type,MT_EMPTY
        .endsw
    .endif

    ; reset redefine

    .if ( CurrStruct == NULL )
        .if ( redef_struct )
            .if ( AreStructsEqual( rdi, redef_struct ) == FALSE )
                asmerr( 2007, szStructure, [rdi].asym.name )
            .endif
            SymFree( rdi )
            mov redef_struct,NULL
        .endif
    .else

        mov rcx,CurrStruct
        mov eax,[rdi].asym.max_mbr_size
        .if ( eax > [rcx].asym.max_mbr_size )
            mov [rcx].asym.max_mbr_size,eax
        .endif

        UpdateStructSize( rdi )
    .endif
    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif
    .return( NOT_ERROR )

EndstructDirective endp


; v2.06: new function to check fields of anonymous struct members

    assume rdi:ptr sfield

CheckAnonymousStruct proc fastcall private uses rdi type_ptr:ptr dsym

    mov rcx,[rcx].dsym.structinfo
    .for ( rdi = [rcx].struct_info.head : rdi : rdi = [rdi].next )

        mov rax,[rdi].name
        .if ( byte ptr [rax] )

            SearchNameInStruct( CurrStruct, [rdi].name, 0, 0 )
            .if ( rax )
                .return( asmerr( 2005, [rax].asym.name ) )
            .endif

        .elseif ( [rdi].type )

            mov rax,[rdi].type
            .if ( [rax].asym.typekind == TYPE_STRUCT ||
                  [rax].asym.typekind == TYPE_UNION )

                .ifd ( CheckAnonymousStruct( rax ) == ERROR )
                    .return( ERROR )
                .endif
            .endif
        .endif
    .endf
    .return( NOT_ERROR )

CheckAnonymousStruct endp


; CreateStructField() - creates a symbol of state SYM_STRUCT_FIELD.
; this function is called in pass 1 only.
; - loc: initializer index location, -1 means no initializer (is an embedded struct)
; - name: field name, may be NULL
; - mem_type: mem_type of item
; - vartype: user-defined type of item if memtype is MT_TYPE
; - size: size of type - used for alignment only

    assume rsi:ptr struct_info

CreateStructField proc __ccall uses rsi rdi rbx loc:int_t, tokenarray:ptr asm_tok,
        name:string_t, mem_type:byte, vartype:ptr asym, size:uint_t

  local offs:int_32
  local len:int_t
  local s:ptr struct_info
  local bitfield:int_t ; don't align bitfields..

    mov bitfield,0
    mov rcx,CurrStruct
    .if ( [rcx].asym.typekind == TYPE_RECORD )
        mov bitfield,1
    .endif
    mov s,[rcx].dsym.structinfo
    mov offs,[rcx].asym.offs

    .if ( name )

        mov len,tstrlen( name )
        .if( eax > MAX_ID_LEN )

            asmerr( 2043 )
           .return( NULL )
        .endif

        SearchNameInStruct( CurrStruct, name, 0, 0 )
        .if ( rax )

            asmerr( 2005, [rax].asym.name )
           .return( NULL )
        .endif

    .else

        ; v2.06: check fields of anonymous struct member

        mov rcx,vartype
        .if ( rcx && ( [rcx].asym.typekind == TYPE_STRUCT || [rcx].asym.typekind == TYPE_UNION ) )
            CheckAnonymousStruct( rcx )
        .endif
        mov name,&@CStr("")
        mov len,0
    .endif

    mov ecx,loc
    .if ( ecx != -1 )

        mov  rdi,StringBufferEnd
        inc  ecx
        imul ebx,ecx,asm_tok
        add  rbx,tokenarray

        .for ( : [rbx].token != T_FINAL : rbx += asm_tok )

            .if ( [rbx].token == T_ID )

                mov rsi,SymSearch( [rbx].string_ptr )
                .if ( eax && [rax].asym.flags & S_VARIABLE )

                    .if ( [rax].asym.flags & S_PREDEFINED && [rax].asym.sfunc_ptr )

                        [rax].asym.sfunc_ptr( rax, NULL )
                        mov rax,rsi
                    .endif

                    xor ecx,ecx
                    .ifs ( [rax].asym.value3264 < 0 )
                        inc ecx
                    .endif

                    mov esi,[rax].asym.uvalue
ifdef _WIN64
                    myltoa( rsi, rdi, MODULE.radix, ecx, TRUE )
else
                    xor edx,edx
                    myltoa( edx::esi, edi, MODULE.radix, ecx, TRUE )
endif
                    add rdi,tstrlen( rdi )
                    mov al,' '
                    stosb
                   .continue
                .endif
            .endif

            mov rsi,[rbx].tokpos
            mov rcx,[rbx+asm_tok].tokpos
            sub rcx,rsi
            rep movsb
        .endf

        mov byte ptr [rdi],0
        mov rcx,rdi
        sub rcx,StringBufferEnd
        mov rsi,rcx
        add ecx,sizeof( sfield )
        mov rdi,LclAlloc( ecx )
        xor eax,eax
        mov ecx,sizeof( sfield )
        mov rdx,rdi
        rep stosb
        lea rdi,[rdx].sfield.ivalue
        mov rcx,rsi
        mov rsi,StringBufferEnd
        inc ecx
        rep movsb
        mov rdi,rdx

    .else

        mov rdi,LclAlloc( sizeof( sfield ) )
        xor eax,eax
        mov ecx,sizeof( sfield )
        mov rdx,rdi
        rep stosb
        mov rdi,rdx
    .endif

    ; create the struct field symbol

    mov [rdi].name_size,len
    .if ( eax )
        mov [rdi].name,LclDup( name )
    .else
        mov [rdi].name,&@CStr("")
    .endif
    mov [rdi].state,SYM_STRUCT_FIELD
    .if ( MODULE.cref )
        or [rdi].flags,S_LIST
    .endif
    or  [rdi].flags,S_ISDEFINED
    mov [rdi].mem_type,mem_type
    mov [rdi].type,vartype
    mov [rdi].next,NULL


    mov rsi,s
    mov rcx,[rsi].head
    .if ( [rsi].head == NULL )
        mov bitfield,0      ; align the first one..
        mov [rsi].head,rdi
        mov [rsi].tail,rdi
    .else
        mov rcx,[rsi].tail
        mov [rcx].sfield.next,rdi
        mov [rsi].tail,rdi
    .endif

    ; v2.0: for STRUCTs, don't use the struct's size for alignment calculations,
    ; instead use the size of the "max" member!
    ; v2.34.14: alias types were skipped...

    mov rcx,vartype
    .if ( mem_type == MT_TYPE )

        .while ( [rcx].asym.type )
            mov rcx,[rcx].asym.type
        .endw
        .if ( [rcx].asym.typekind == TYPE_STRUCT || [rcx].asym.typekind == TYPE_UNION )
            mov size,[rcx].asym.max_mbr_size
        .endif
    .endif

    ; align the field if an alignment argument was given

    movzx eax,[rsi].alignment

    .if ( eax > 1 && bitfield == 0 )

        ; if it's the first field to add, use offset of the parent's current field

        mov ecx,size

        .if ( eax < ecx )

            lea ecx,[rax-1]
            mov edx,offs
            add edx,ecx
            neg eax
            and edx,eax
            mov offs,edx

        .elseif ( ecx )

            mov eax,ecx
            lea ecx,[rax-1]
            mov edx,offs
            add edx,ecx
            neg eax
            and edx,eax
            mov offs,edx

        .endif

        ; adjust the struct's current offset + size.
        ; The field's size is added in UpdateStructSize()

        mov rcx,CurrStruct
        .if ( [rcx].asym.typekind != TYPE_UNION )
            mov [rcx].asym.offs,offs
            .if ( offs > [rcx].asym.total_size )
                mov [rcx].asym.total_size,offs
            .endif
        .endif
    .endif

    mov rcx,CurrStruct
    .if ( size > [rcx].asym.max_mbr_size )
        mov [rcx].asym.max_mbr_size,size
    .endif
    mov [rdi].offs,offs

    ; if -Zm is on, create a global symbol

    mov rdx,name
    .if ( MODULE.oldstructs == TRUE && byte ptr [rdx] )

        SymLookup( name )
        .if ( [rax].asym.state == SYM_UNDEFINED )
            mov [rax].asym.state,SYM_STRUCT_FIELD
        .endif

        .if ( [rax].asym.state == SYM_STRUCT_FIELD )

            mov rcx,rax
            mov [rcx].asym.mem_type,mem_type
            mov [rcx].asym.type,vartype
            mov [rcx].asym.offs,offs ; added v2.0

            ; v2.01: must be the full offset.
            ; (there's still a problem if alignment is > 1!)

            mov rdx,CurrStruct
            .for ( rdx = [rdx].dsym.next : rdx : rdx = [rdx].dsym.next )
                add [rcx].asym.offs,[rdx].asym.offs
            .endf
            or [rcx].asym.flags,S_ISDEFINED
        .endif
    .endif
    .return( rdi )

CreateStructField endp


; called by AlignDirective() if ALIGN/EVEN has been found inside
; a struct. It's already verified that <value> is a power of 2.

AlignInStruct proc fastcall value:int_t

    mov rdx,CurrStruct

    .if ( [rdx].asym.typekind != TYPE_UNION )

        mov eax,[rdx].asym.offs
        lea eax,[rax+rcx-1]
        neg ecx
        and eax,ecx
        mov [rdx].asym.offs,eax

        .if ( eax > [rdx].asym.total_size )
            mov [rdx].asym.total_size,eax
        .endif
    .endif
    .return( NOT_ERROR )

AlignInStruct endp


; called by data_dir() when a structure field has been created.

UpdateStructSize proc fastcall sym:ptr asym

    mov rdx,CurrStruct
    .if ( [rdx].asym.typekind == TYPE_RECORD )
        ;
    .elseif ( [rdx].asym.typekind == TYPE_UNION )
        .if ( [rcx].asym.total_size > [rdx].asym.total_size )
            mov [rdx].asym.total_size,[rcx].asym.total_size
        .endif
    .else
        add [rdx].asym.offs,[rcx].asym.total_size
        .ifs ( [rdx].asym.offs > [rdx].asym.total_size )
            mov [rdx].asym.total_size,[rdx].asym.offs
        .endif
    .endif
    ret

UpdateStructSize endp


; called if ORG occurs inside STRUCT/UNION definition

SetStructCurrentOffset proc fastcall off:int_t

    mov rdx,CurrStruct
    .if ( [rdx].asym.typekind == TYPE_UNION )
        .return( asmerr( 2200 ) )
    .endif
    mov [rdx].asym.offs,ecx

    ; if an ORG is inside the struct, it cannot be instanced anymore

    mov rax,[rdx].dsym.structinfo
    or [rax].struct_info.flags,SI_ORGINSIDE

    .ifs ( ecx > [rdx].asym.total_size )
        mov [rdx].asym.total_size,ecx
    .endif
    .return( NOT_ERROR )

SetStructCurrentOffset endp


; get a qualified type.
; Used by
; - TYPEDEF
; - PROC/PROTO params and LOCALs
; - EXTERNDEF
; - EXTERN
; - LABEL
; - ASSUME for GPRs

    assume rsi:ptr qualified_type
    assume rdi:nothing

GetQualifiedType proc __ccall uses rsi rdi rbx pi:ptr int_t, tokenarray:ptr asm_tok,
        pti:ptr qualified_type

   .new type:int_t
   .new tmp:int_t
   .new mem_type:byte
   .new distance:int_t = FALSE
   .new i:int_t

    ldr rcx,pi
    ldr rdx,tokenarray

    mov eax,[rcx]
    mov i,eax

    imul ebx,eax,asm_tok
    add  rbx,rdx
    mov  rdx,rbx

    ; convert PROC token to a type qualifier

    .for ( : [rbx].token != T_FINAL && [rbx].token != T_COMMA : rbx += asm_tok )

        .if ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_PROC )

            mov [rbx].token,T_STYPE

            ; v2.06: avoid to use ST_PROC

            mov cl,MODULE._model
            mov eax,1
            shl eax,cl
            and eax,SIZE_CODEPTR
            mov ecx,T_NEAR
            .ifnz
                mov ecx,T_FAR
            .endif
            mov [rbx].tokval,ecx
        .endif
    .endf
    mov rbx,rdx

    ; with NEAR/FAR, there are several syntax variants allowed:
    ; 1. NEARxx | FARxx
    ; 2. PTR NEARxx | FARxx
    ; 3. NEARxx | FARxx PTR [<type>]

    ; read qualified type

    mov rsi,pti
    .for ( type = ERROR : [rbx].token == T_STYPE || [rbx].token == T_BINARY_OPERATOR : rbx += asm_tok )

        .if ( [rbx].token == T_STYPE )

            mov edi,[rbx].tokval
            .if ( type == ERROR )
                mov type,edi
            .endif
            mov mem_type,GetMemtypeSp( edi )

            .if ( al == MT_FAR || al == MT_NEAR )

                .if ( distance == FALSE )

                    mov eax,GetSflagsSp( edi )
                    cmp mem_type,MT_FAR
                    setz cl
                    mov [rsi].is_far,cl

                    .if ( eax != USE_EMPTY )
                        mov [rsi].Ofssize,al
                    .endif
                    mov distance,TRUE

                .elseif ( [rbx-asm_tok].tokval != T_PTR )

                    .break
                .endif

            .else

                .if ( [rsi].is_ptr )
                    mov [rsi].ptr_memtype,mem_type
                .endif
                add rbx,asm_tok
                .break
            .endif

        .elseif ( [rbx].tokval == T_PTR )

            mov type,EMPTY
            inc [rsi].is_ptr

        .else
            .break
        .endif
    .endf

    .if ( type == EMPTY )

        .if ( [rbx].token == T_ID && [rbx-asm_tok].tokval == T_PTR )

            mov [rsi].symtype,SymSearch( [rbx].string_ptr )
            mov rdi,[rsi].symtype

            .if ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )

                ;.if ( rdi && rdi == CurrStruct )
                ;.else
                    mov [rsi].symtype,CreateTypeSymbol( rdi, [rbx].string_ptr, TRUE )
                ;.endif

            .elseif ( [rdi].asym.state != SYM_TYPE )

                .return( asmerr( 2004, [rbx].string_ptr ) )

            .else

                ; if it's a typedef, simplify the info

                .if ( [rdi].asym.typekind == TYPE_TYPEDEF )

                    add [rsi].is_ptr,[rdi].asym.is_ptr
                    .if ( [rdi].asym.is_ptr == 0 )

                        mov al,MT_EMPTY
                        .if ( [rdi].asym.mem_type != MT_TYPE )
                            mov al,[rdi].asym.mem_type
                        .endif
                        mov [rsi].ptr_memtype,al

                        .if ( distance == FALSE && [rsi].is_ptr == 1 && ( [rdi].asym.mem_type == MT_NEAR ||
                              [rdi].asym.mem_type == MT_PROC || [rdi].asym.mem_type == MT_FAR ) )

                            mov [rsi].is_far,[rdi].asym.is_far
                            .if ( [rdi].asym.Ofssize != USE_EMPTY )
                                mov [rsi].Ofssize,[rdi].asym.Ofssize
                            .endif
                        .endif

                    .else

                        mov [rsi].ptr_memtype,[rdi].asym.ptr_memtype
                        .if ( distance == FALSE && [rsi].is_ptr == 1 )

                            mov [rsi].is_far,[rdi].asym.is_far
                            .if ( [rdi].asym.Ofssize != USE_EMPTY )
                                mov [rsi].Ofssize,[rdi].asym.Ofssize
                            .endif
                        .endif
                    .endif

                    .if ( [rdi].asym.mem_type == MT_TYPE )
                        mov [rsi].symtype,[rdi].asym.type
                    .else
                        mov [rsi].symtype,[rdi].asym.target_type
                    .endif
                .endif
            .endif
            add rbx,asm_tok
        .endif
    .endif

    .if ( type == ERROR )

        .if ( [rbx].token != T_ID )

            .if ( [rbx].token == T_FINAL || [rbx].token == T_COMMA )
                asmerr( 2175 )
            .else
                asmerr( 2008, [rbx].string_ptr )
                ;add rbx,asm_tok
            .endif
            .return( ERROR )
        .endif

        mov [rsi].symtype,SymSearch( [rbx].string_ptr )
        mov rdi,rax

        .if ( rdi == NULL || [rdi].asym.state != SYM_TYPE )
            .if ( [rsi].symtype == NULL || [rdi].asym.state == SYM_UNDEFINED )
                asmerr( 2006, [rbx].string_ptr )
            .else
                asmerr( 2004, [rbx].string_ptr )
            .endif
            .return( ERROR )
        .endif

        mov rdi,[rsi].symtype
        .if ( [rdi].asym.typekind == TYPE_TYPEDEF )

            mov [rsi].mem_type,[rdi].asym.mem_type
            mov [rsi].is_far,[rdi].asym.is_far
            mov [rsi].is_ptr,[rdi].asym.is_ptr
            mov [rsi].Ofssize,[rdi].asym.Ofssize
            mov [rsi].size,[rdi].asym.total_size
            mov [rsi].ptr_memtype,[rdi].asym.ptr_memtype
            .if ( [rdi].asym.mem_type == MT_TYPE )
                mov [rsi].symtype,[rdi].asym.type
            .else
                mov [rsi].symtype,[rdi].asym.target_type
            .endif

        .else
            mov [rsi].mem_type,MT_TYPE
            mov [rsi].size,[rdi].asym.total_size
        .endif
        add rbx,asm_tok

    .else

        .if ( [rsi].is_ptr )
            mov [rsi].mem_type,MT_PTR
        .else
            mov [rsi].mem_type,GetMemtypeSp( type )
        .endif

        .if ( [rsi].mem_type == MT_PTR )

            ; v2.16: if pointer to data and no distance entered, use memory model to set pointer distance

            .if ( distance == FALSE && !( [rsi].ptr_memtype &  MT_SPECIAL_MASK ) )

                xor     eax,eax
                mov     edx,1
                mov     cl,MODULE._model
                shl     edx,cl
                test    edx,SIZE_DATAPTR
                setnz   al
                mov     [rsi].is_far,al
            .endif

            mov ecx,MT_NEAR
            .if ( [rsi].is_far )
                mov ecx,MT_FAR
            .endif
            mov [rsi].size,SizeFromMemtype( cl, [rsi].Ofssize, NULL )
        .else
            mov [rsi].size,SizeFromMemtype( [rsi].mem_type, [rsi].Ofssize, NULL )
        .endif
    .endif

    mov rax,rbx
    sub rax,tokenarray
    xor edx,edx
    mov ecx,asm_tok
    div ecx
    mov rcx,pi
    mov [rcx],eax
   .return( NOT_ERROR )

GetQualifiedType endp


; TYPEDEF directive. Syntax is:
; <type name> TYPEDEF [proto|[far|near [ptr]]<qualified type>]

CreateType proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok, name:string_t, pp:ptr asym

  local ti:qualified_type

    mov rdi,SymSearch( name )
    .if ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )

        mov rdi,CreateTypeSymbol( rdi, name, TRUE )
        .if ( rdi == NULL )
            .return( ERROR )
        .endif

if TYPEOPT
        ; release the structinfo data extension
        mov [rdi].dsym.structinfo,NULL
endif

    .else

        ; MASM allows to have the TYPEDEF included multiple times
        ; but the types must be identical!

        .if ( ( [rdi].asym.state != SYM_TYPE ) ||
              ( [rdi].asym.typekind != TYPE_TYPEDEF && [rdi].asym.typekind != TYPE_NONE ) )

            .return( asmerr( 2005, [rdi].asym.name ) )
        .endif
    .endif

    mov rcx,pp
    .if ( rcx )
        mov [rcx],rdi
    .endif

    or [rdi].asym.flags,S_ISDEFINED
    .if ( rcx == NULL && Parse_Pass > PASS_1 )
        .return( NOT_ERROR )
    .endif
    mov [rdi].asym.typekind,TYPE_TYPEDEF
    imul ebx,i,asm_tok
    add  rbx,tokenarray

    ; PROTO is special

    .if ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_PROTO )

        ; v2.04: added check if prototype is set already

        .if ( [rdi].asym.target_type == NULL && [rdi].asym.mem_type == MT_EMPTY )
            CreateProc( NULL, "", SYM_TYPE )
        .elseif ( [rdi].asym.mem_type == MT_PROC )
            mov rax,[rdi].asym.target_type
        .else
            .return( asmerr( 2004, [rdi].asym.name ) )
        .endif

        inc i
        mov rsi,rax
        .return .ifd ( ParseProc( rsi, i, tokenarray, FALSE, MODULE.langtype ) == ERROR )

        assume rsi:nothing

        mov [rdi].asym.mem_type,MT_PROC
        mov [rdi].asym.Ofssize,[rsi].asym.segoffsize

        ; v2.03: set value of field total_size (previously was 0)

        mov eax,2
        mov cl,[rdi].asym.Ofssize
        shl eax,cl
        mov [rdi].asym.total_size,eax

        .if ( [rsi].asym.mem_type != MT_NEAR )

            mov [rdi].asym.is_far,1 ; v2.04: added
            add [rdi].asym.total_size,2
        .endif

        mov [rdi].asym.target_type,rsi
       .return( NOT_ERROR )
    .endif

    mov ti.size,0
    mov ti.is_ptr,0
    mov ti.is_far,FALSE
    mov cl,MODULE._model
    mov eax,1
    shl eax,cl
    .if eax & SIZE_DATAPTR
        mov ti.is_far,TRUE ; added v2.33.33
    .endif

    mov ti.mem_type,MT_EMPTY
    mov ti.ptr_memtype,MT_EMPTY
    mov ti.symtype,NULL
    mov ti.Ofssize,MODULE.Ofssize

    ; "empty" type is ok for TYPEDEF

    .if ( [rbx].token == T_FINAL || [rbx].token == T_COMMA )
        ;
    .elseifd ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
        .return
    .endif

    ; if type did exist already, check for type conflicts
    ; v2.05: this code has been rewritten

    .if ( [rdi].asym.mem_type != MT_EMPTY )

        .for( rcx = ti.symtype : rcx && [rcx].asym.type : rcx = [rcx].asym.type )
        .endf

        mov rdx,[rdi].asym.target_type
        .if ( [rdi].asym.mem_type == MT_TYPE )
            mov rdx,[rdi].asym.type
        .endif

        .for( : rdx && [rdx].asym.type : rdx = [rdx].asym.type )
        .endf

        mov bl,MODULE.Ofssize
        mov bh,bl
        .if ( [rdi].asym.Ofssize != USE_EMPTY )
            mov bl,[rdi].asym.Ofssize
        .endif
        .if ( ti.Ofssize != USE_EMPTY )
            mov bh,ti.Ofssize
        .endif

        cmp bl,bh
        setnz bl

        .if ( ti.mem_type != [rdi].asym.mem_type ||
            ( ti.mem_type == MT_TYPE && rcx != rdx ) ||
            ( ti.mem_type == MT_PTR &&
            ( ti.is_far != [rdi].asym.is_far || bl ||
              ti.ptr_memtype != [rdi].asym.ptr_memtype || rcx != rdx ) ) )

            .return( asmerr( 2004, name ) )
        .endif
    .endif

    mov [rdi].asym.mem_type,ti.mem_type
    mov [rdi].asym.Ofssize,ti.Ofssize
    mov [rdi].asym.total_size,ti.size
    mov [rdi].asym.is_ptr,ti.is_ptr
    mov [rdi].asym.is_far,ti.is_far

    .if ( ti.mem_type == MT_TYPE )
        mov [rdi].asym.type,ti.symtype
    .else
        mov [rdi].asym.target_type,ti.symtype
    .endif

    mov [rdi].asym.ptr_memtype,ti.ptr_memtype
    imul ebx,i,asm_tok
    add  rbx,tokenarray

    .if ( pp == NULL && [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif
    .return( NOT_ERROR )

CreateType endp


TypedefDirective proc __ccall i:int_t, tokenarray:ptr asm_tok

    ldr ecx,i
    ldr rdx,tokenarray
    .if( ecx != 1 )
        imul eax,ecx,asm_tok
        .return( asmerr( 2008, [rdx+rax].asm_tok.string_ptr ) )
    .endif
    inc ecx
   .return( CreateType( ecx, rdx, [rdx].asm_tok.string_ptr, NULL ) )

TypedefDirective endp


; RECORD directive
; syntax: <label> RECORD <bitfield_name>:<size>[,...]
; defines a RECORD type (state=SYM_TYPE).
; the memtype will be MT_BYTE, MT_WORD, MT_DWORD [, MT_QWORD in 64-bit].

RecordDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

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

    ldr ecx,i
    ldr rbx,tokenarray
    mov name,[rbx].string_ptr
    imul ecx,ecx,asm_tok
    add rbx,rcx

    .if ( i != 1 )
        .if ( i == 0 )
            .return StructDirective( i, tokenarray )
        .endif
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif

    mov rsi,SymSearch( name )

    .if ( rsi == NULL || [rsi].asym.state == SYM_UNDEFINED )

        mov rsi,CreateTypeSymbol( rsi, name, TRUE )

    .elseif ( [rsi].asym.state == SYM_TYPE &&
             ( [rsi].asym.typekind == TYPE_RECORD || [rsi].asym.typekind == TYPE_NONE ) )

        ; v2.04: allow redefinition of record and forward references.
        ; the record redefinition may have different initial values,
        ; but those new values are IGNORED! ( Masm bug? )

        .if ( Parse_Pass == PASS_1 && [rsi].asym.typekind == TYPE_RECORD )

            mov oldr,rsi
            mov rsi,CreateTypeSymbol( NULL, name, FALSE )
            mov redef_err,0
        .endif
    .else
        .return( asmerr( 2005, name ) )
    .endif

    or [rsi].asym.flags,S_ISDEFINED

    .if ( Parse_Pass > PASS_1 )
        .return( NOT_ERROR )
    .endif

    mov newr,rsi
    mov [rsi].asym.typekind,TYPE_RECORD

    inc i ; go past RECORD
    add rbx,asm_tok

    mov cntBits,0 ; counter for total of bits in record

    ; parse bitfields

    .repeat

        .if ( [rbx].token != T_ID )

            asmerr( 2008, [rbx].string_ptr )
           .break
        .endif

        mov len,tstrlen( [rbx].string_ptr )
        .if ( eax > MAX_ID_LEN )

            asmerr( 2043 )
           .break
        .endif

        mov rdi,rbx
        inc i
        .if ( [rbx+asm_tok].token != T_COLON )

            asmerr( 2065, "" )
           .break
        .endif

        inc i

        ; get width

        .break .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) == ERROR )

        .if ( opndx.kind != EXPR_CONST )

            asmerr( 2026 )
            mov opndx.value,1
        .endif

        mov ecx,opndx.value
        add ecx,cntBits
        mov eax,32
        .if ( MODULE.Ofssize == USE64 )
            mov eax,64
        .endif
        .if ( opndx.value == 0 )

            asmerr( 2172, [rbx].string_ptr )
           .break

        .elseif ( ecx > eax )

            asmerr( 2089, [rbx].string_ptr )
           .break
        .endif
        mov count,0

        ; is there an initializer? ('=')

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( [rbx].token == T_DIRECTIVE && [rbx].dirtype == DRT_EQUALSGN )

            inc i
            add rbx,asm_tok
            mov rcx,rbx
            mov init_loc,rbx
            .for( : [rbx].token != T_FINAL && [rbx].token != T_COMMA: i++, rbx += asm_tok )
            .endf
            ; no value?
            .if ( rcx == rbx )
                asmerr( 2008, [rdi].asm_tok.tokpos )
                .break
            .endif
            ; v2.09: initial values of record redefinitions are ignored!
            .if ( oldr == NULL )
                mov rax,[rbx].tokpos
                sub rax,[rcx].asm_tok.tokpos
                mov count,eax
            .endif
        .endif

        ; record field names are global! (Masm design flaw)

        mov rsi,SymSearch( [rdi].asm_tok.string_ptr )
        mov def,TRUE

        .if ( oldr )

            .if ( rsi == NULL || [rsi].asym.state != SYM_STRUCT_FIELD ||
                  [rsi].asym.mem_type != MT_BITS || [rsi].asym.total_size != opndx.value )

                asmerr( 2007, szRecord, [rdi].asm_tok.string_ptr )
                inc redef_err
                mov def,FALSE ; v2.06: added
            .endif

        .elseif ( rsi )

            asmerr( 2005, [rsi].asym.name )
           .break
        .endif

        .if ( def ) ; v2.06: don't add field if there was an error

            mov rsi,[rdi].asm_tok.string_ptr
            add cntBits,opndx.value
            mov ecx,count
            mov rdx,LclAlloc( &[rcx+sizeof( sfield )] )
            mov ecx,sizeof( sfield )
            mov rdi,rax
            xor eax,eax
            rep stosb
            mov rdi,rdx
            assume rdi:ptr sfield

            mov [rdi].name_size,len
            mov [rdi].name,LclDup( rsi )
            and [rdi].flags,not S_LIST
            .if ( MODULE.cref )
                or [rdi].flags,S_LIST
            .endif
            mov [rdi].state,SYM_STRUCT_FIELD
            mov [rdi].mem_type,MT_BITS
            mov [rdi].total_size,opndx.value

            .if ( !oldr )
                SymAddGlobal( rdi )
            .endif

            mov [rdi].next,NULL
            mov [rdi].ivalue[0],0
            mov rcx,newr
            mov rcx,[rcx].dsym.structinfo

            .if ( [rcx].struct_info.head == NULL )

                mov [rcx].struct_info.head,rdi
                mov [rcx].struct_info.tail,rdi
            .else

                mov rdx,[rcx].struct_info.tail
                mov [rdx].sfield.next,rdi
                mov [rcx].struct_info.tail,rdi
            .endif

            .if ( count )

                mov rcx,init_loc
                mov rdx,rdi
                mov rsi,[rcx].asm_tok.tokpos
                lea rdi,[rdi].ivalue
                mov ecx,count
                rep movsb
                mov byte ptr [rdi],0
                mov rdi,rdx
            .endif
        .endif

        .if ( i < TokenCount )

            .if ( [rbx].token != T_COMMA || [rbx+asm_tok].token == T_FINAL )
                asmerr(2008, [rbx].tokpos )
               .break
            .endif

            inc i
            add rbx,asm_tok
        .endif

    .until ( i >= TokenCount )

    ; now calc size in bytes and set the bit positions

    mov rsi,newr
    mov eax,cntBits

    .if ( eax > 16 )

        .if ( eax > 32 )
            mov [rsi].asym.total_size,QWORD
            mov [rsi].asym.mem_type,MT_QWORD
        .else
            mov [rsi].asym.total_size,DWORD
            mov [rsi].asym.mem_type,MT_DWORD
        .endif

    .elseif ( eax > 8 )

        mov [rsi].asym.total_size,WORD
        mov [rsi].asym.mem_type,MT_WORD

    .else

        mov [rsi].asym.total_size,BYTE
        mov [rsi].asym.mem_type,MT_BYTE
    .endif

    ; if the BYTE/WORD/DWORD isn't used fully, shift bits to the right!
    ; set the bit position

    mov rcx,[rsi].dsym.structinfo
    .for ( rdi = [rcx].struct_info.head: rdi: rdi = [rdi].next )

        sub eax,[rdi].total_size
        mov [rdi].offs,eax
    .endf

    .if ( oldr )

        mov eax,1
        .if ( redef_err > 0 )
            dec eax
        .else
            AreStructsEqual( newr, oldr )
        .endif
        .if ( eax == FALSE )
            asmerr( 2007, szRecord, [rsi].asym.name )
        .endif

        ; record can be freed, because the record's fields are global items.
        ; And initial values of the new definition are ignored!

        SymFree( newr )
    .endif
    .return( NOT_ERROR )

RecordDirective endp

    end
