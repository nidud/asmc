; SEGMENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Processing of segment and group related directives:
; - SEGMENT, ENDS, GROUP
;

include asmc.inc
include memalloc.inc
include parser.inc
include reswords.inc
include segment.inc
include expreval.inc
include omf.inc
include omfspec.inc
include fastpass.inc
include coffspec.inc
include assume.inc
include listing.inc
include types.inc
include fixup.inc
include label.inc

public CV8Label
public symCurSeg

define INIT_ATTR            0x01 ; READONLY attribute
define INIT_ALIGN           0x02 ; BYTE, WORD, PARA, DWORD, ...
define INIT_ALIGN_PARAM     (0x80 or INIT_ALIGN) ; ALIGN(x)
define INIT_COMBINE         0x04 ; PRIVATE, PUBLIC, STACK, COMMON
define INIT_COMBINE_AT      (0x80 or INIT_COMBINE) ; AT
define INIT_COMBINE_COMDAT  (0xC0 or INIT_COMBINE) ; COMDAT
define INIT_OFSSIZE         0x08 ; USE16, USE32, ...
define INIT_OFSSIZE_FLAT    (0x80 or INIT_OFSSIZE) ; FLAT
define INIT_ALIAS           0x10 ; ALIAS(x)
define INIT_CHAR            0x20 ; DISCARD, SHARED, EXECUTE, ...
define INIT_CHAR_INFO       (0x80 or INIT_CHAR) ; INFO

define INIT_EXCL_MASK     0x1F   ; exclusive bits

.template typeinfo
    value   db ?    ; value assigned to the token
    init    db ?    ; kind of token
   .ends

.data

CV8Label    asym_t 0 ; Start label for Code View 8
symCurSeg   asym_t 0 ; @CurSeg symbol

sitem macro text, value, init
    exitm<string_t @CStr(text)>
    endm

SegAttrToken label string_t
include segattr.inc
size_SegAttrToken equ ($ - SegAttrToken)
count_SegAttrToken equ (size_SegAttrToken / string_t)

undef sitem
sitem macro text, value, init
    exitm<typeinfo { value, init }>
    endm
SegAttrValue label typeinfo
include segattr.inc
undef sitem

align 4
grpdefidx   dd 0    ; Number of group definitions
align 8
SegStack    asym_t MAX_SEG_NESTING dup(0) ; stack of open segments
stkindex    int_t 0 ; current top of stack

; saved state
align 8
saved_CurrSeg   asym_t 0
saved_SegStack  ptr asym_t 0
saved_stkindex  int_t 0

; generic byte buffer, used for OMF LEDATA records only
align 8
codebuf         db 1024 dup(0)
buffer_size     dd 0 ; total size of code buffer

; min cpu for USE16, USE32 and USE64
min_cpu         dw P_86, P_386, P_64
ImageBase       db 0

.code

; find token in a string table

FindToken proc __ccall private uses rsi rdi token:string_t, table:ptr, size:int_t

    ldr rsi,table

    .for ( edi = 0 : edi < size : edi++, rsi+=string_t )
        .ifd ( tstricmp( [rsi], token ) == 0 )
            .return( edi )
        .endif
    .endf
    .return( -1 ) ; Not found

FindToken endp


; set value of $ symbol

UpdateCurPC proc fastcall sym:asym_t, p:ptr

    mov rdx,CurrStruct

    .if ( rdx )

        mov [rcx].asym.mem_type,MT_EMPTY
        mov [rcx].asym.segm,NULL ; v2.07: needed again
        mov eax,[rdx].asym.offs
        .if [rdx].asym.next
            mov rdx,[rdx].asym.next
            add eax,[rdx].asym.offs
        .endif
        mov [rcx].asym.offs,eax

    .elseif ( CurrSeg )  ; v2.10: check for CurrSeg != NULL

        mov [rcx].asym.mem_type,MT_NEAR
        mov [rcx].asym.segm,CurrSeg
        mov [rcx].asym.offs,GetCurrOffset()
    .else
        asmerr( 2034 ) ; v2.10: added
    .endif
    ret

UpdateCurPC endp


AddLnameItem proc fastcall private sym:asym_t

    QAddItem( &MODULE.LnameQueue, rcx )
    ret

AddLnameItem endp


; what's inserted into the LNAMES queue:
; SYM_SEG: segment names
; SYM_GRP: group names
; SYM_CLASS_LNAME : class names

FreeLnameQueue proc private uses rsi rdi

    .for ( rdi = MODULE.LnameQueue.head: rdi: rdi = rsi )
        mov rsi,[rdi].qnode.next

        ; the class name symbols are not part of the
        ; symbol table and hence must be freed now.

        mov rcx,[rdi].qnode.sym
        .if ( [rcx].asym.state == SYM_CLASS_LNAME )
            SymFree( rcx )
        .endif
    .endf
    ret

FreeLnameQueue endp


; set CS assume entry whenever current segment is changed.
; Also updates values of text macro @CurSeg.

UpdateCurrSegVars proc private uses rsi rdi

    mov rcx,symCurSeg
    mov rdi,CurrSeg
    lea rax,SegAssumeTable
    lea rsi,[rax+ASSUME_CS*assume_info]

    .if ( rdi == NULL )

        mov [rsi].assume_info.symbol,NULL
        mov [rsi].assume_info.is_flat,FALSE
        mov [rsi].assume_info.error,TRUE
        mov [rcx].asym.string_ptr,&@CStr("")
    .else

        mov [rsi].assume_info.is_flat,FALSE
        mov [rsi].assume_info.error,FALSE

        ; fixme: OPTION OFFSET:SEGMENT?

        mov rdx,[rdi].asym.seginfo

        .if ( [rdx].seg_info.sgroup != NULL )

            mov [rsi].assume_info.symbol,[rdx].seg_info.sgroup
            .if ( rax == MODULE.flat_grp )
                mov [rsi].assume_info.is_flat,TRUE
            .endif
        .else
            mov [rsi].assume_info.symbol,rdi
        .endif
        mov [rcx].asym.string_ptr,[rdi].asym.name
    .endif
    ret

UpdateCurrSegVars endp


push_seg proc fastcall private s:asym_t

    ; Push a segment into the current segment stack

    mov edx,stkindex
    .if ( edx >= MAX_SEG_NESTING )
        .return asmerr( 1007 )
    .endif
    inc stkindex
    mov rax,CurrSeg
    mov CurrSeg,rcx
    lea rcx,SegStack
    mov [rcx+rdx*size_t],rax
    UpdateCurrSegVars()
    ret

push_seg endp


pop_seg proc private

    ; Pop a segment out of the current segment stack

    ; it's already checked that CurrSeg is != NULL, so
    ; stkindex must be > 0, but anyway ...

    .if ( stkindex )

        dec stkindex
        mov ecx,stkindex
        lea rdx,SegStack
        mov CurrSeg,[rdx+rcx*size_t]
        UpdateCurrSegVars()
    .endif
    ret

pop_seg endp


GetCurrOffset proc

    mov rax,CurrSeg
    .if rax
        mov rax,[rax].asym.seginfo
        mov eax,[rax].seg_info.current_loc
    .endif
    ret

GetCurrOffset endp


GetCurrSegAlign proc

    mov rax,CurrSeg
    .return .if ( rax == NULL )

    mov rcx,[rax].asym.seginfo
    .if ( [rcx].seg_info.alignment == MAX_SEGALIGNMENT ) ; ABS?
        .return( 0x10 ) ; assume PARA alignment for AT segments
    .endif
    mov cl,[rcx].seg_info.alignment
    mov eax,1
    shl eax,cl
    ret

GetCurrSegAlign endp


CreateGroup proc fastcall private uses rsi rdi name:string_t

    mov rsi,rcx
    mov rdi,SymSearch( rcx )

    .if ( rdi == NULL || [rdi].asym.state == SYM_UNDEFINED )

        .if ( rdi == NULL )
            mov rdi,SymCreate( rsi )
        .else
            sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rdi )
        .endif

        mov [rdi].asym.state,SYM_GRP
        mov [rdi].asym.grpinfo,LclAlloc( sizeof( grp_info ) )
        sym_add_table( &SymTables[TAB_GRP*symbol_queue], rdi )

        mov [rdi].asym.list,1
        mov [rdi].asym.Ofssize, USE_EMPTY ; v2.14: added
        mov rcx,[rdi].asym.grpinfo
        inc grpdefidx
        mov [rcx].grp_info.grp_idx,grpdefidx
        AddLnameItem( rdi )

    .elseif ( [rdi].asym.state != SYM_GRP )

        asmerr( 2005, rsi )
       .return( NULL )
    .endif

    mov [rdi].asym.isdefined,1
   .return( rdi )

CreateGroup endp


CreateSegment proc fastcall private uses rdi s:asym_t, name:string_t, add_global:int_t

    mov rdi,rcx
    .if ( rcx == NULL )

        .if ( add_global )
            SymCreate( rdx )
        .else
            SymAlloc( rdx )
        .endif
        mov rdi,rax

    .elseif ( [rdi].asym.state == SYM_UNDEFINED )

        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rdi )
    .endif

    .if ( rdi )

        mov [rdi].asym.state,SYM_SEG
        mov [rdi].asym.seginfo,LclAlloc( sizeof( seg_info ) )
        mov rcx,rax
        mov [rcx].seg_info.Ofssize,MODULE.defOfssize
        mov [rcx].seg_info.alignment,4 ; this is PARA (2^4)
        mov [rcx].seg_info.combine,COMB_INVALID

        ; null class name, in case none is mentioned

        mov [rdi].asym.next,NULL

        ; don't use sym_add_table(). Thus the "prev" member
        ; becomes free for another use.

        .if ( SymTables[TAB_SEG*symbol_queue].head == NULL )

            mov SymTables[TAB_SEG*symbol_queue].head,rdi
            mov SymTables[TAB_SEG*symbol_queue].tail,rdi
        .else

            mov rcx,SymTables[TAB_SEG*symbol_queue].tail
            mov [rcx].asym.next,rdi
            mov SymTables[TAB_SEG*symbol_queue].tail,rdi
        .endif
    .endif
    .return( rdi )

CreateSegment endp


; handle GROUP directive

    assume rbx:token_t

GrpDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local name:string_t

    ; GROUP directive must be at pos 1, needs a name at pos 0

    ldr rbx,tokenarray
    .if ( i != 1 )

        imul ecx,i,asm_tok
       .return( asmerr( 2008, [rbx+rcx].string_ptr ) )
    .endif

    ; GROUP isn't valid for COFF/ELF/BIN-PE

    .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF ||
         ( Options.output_format == OFORMAT_BIN && MODULE.sub_format == SFORMAT_PE ) )

        .return( asmerr( 2214 ) )
    .endif

    mov rdi,CreateGroup( [rbx].string_ptr )
    .if ( rdi == NULL )
        .return( ERROR )
    .endif

    inc i ; go past GROUP
    add rbx,asm_tok*2

    .repeat

        ; get segment name

        .if ( [rbx].token != T_ID )
            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif

        mov name,[rbx].string_ptr
        inc i
        add rbx,asm_tok

        mov rsi,SymSearch( name )

        .if ( Parse_Pass == PASS_1 )

            .if ( rsi )

                mov rcx,[rsi].asym.seginfo
                xor eax,eax
                .if ( rcx )
                    mov rax,[rcx].seg_info.sgroup
                .endif
            .endif

            .if ( rsi == NULL || [rsi].asym.state == SYM_UNDEFINED )

                mov rsi,CreateSegment( rsi, name, TRUE )

                ; inherit the offset magnitude from the group

                mov rdx,[rdi].asym.grpinfo
                mov rcx,[rsi].asym.seginfo
                .if ( [rdx].grp_info.seglist )
                    mov [rcx].seg_info.Ofssize,[rdi].asym.Ofssize
                .else

                    ; v2.14: reset the default offset size to "undefined", to avoid
                    ; an error when the segment is actually defined (group5.asm)

                    mov [rcx].seg_info.Ofssize,USE_EMPTY
                .endif

            .elseif ( [rsi].asym.state != SYM_SEG )

                .return( asmerr( 2097, name ) )

                ; v2.09: allow segments in FLAT magic group be moved to a "real" group

            .elseif ( rax && rax != MODULE.flat_grp && rax != rdi )

                ; segment is in another group

                .return( asmerr( 2072, name ) )
            .endif

            ; the first segment will define the group's word size
            ; v2.14: set the group's word size until it's != USE_EMPTY

            .if ( [rdi].asym.Ofssize == USE_EMPTY )
                mov [rdi].asym.Ofssize,[rcx].seg_info.Ofssize
            .elseif ( [rdi].asym.Ofssize != [rcx].seg_info.Ofssize )
                .return( asmerr( 2100, [rdi].asym.name, [rsi].asym.name ) )
            .endif
        .else
            .if ( rsi == NULL || [rsi].asym.state != SYM_SEG || [rsi].asym.segm == NULL )
                .return( asmerr( 2006, name ) )
            .endif
        .endif

        ; insert segment in group if it's not there already

        mov rcx,[rsi].asym.seginfo
        .if ( [rcx].seg_info.sgroup == NULL )

            ; set the segment's grp

            mov [rcx].seg_info.sgroup,rdi

            LclAlloc( sizeof( seg_item ) )
            mov [rax].seg_item.iseg,rsi
            mov rdx,[rdi].asym.grpinfo
            inc [rdx].grp_info.numseg

            ; insert the segment at the end of linked list

            .if ( [rdx].grp_info.seglist == NULL )
                mov [rdx].grp_info.seglist,rax
            .else
                mov rcx,[rdx].grp_info.seglist
                .while ( [rcx].seg_item.next != NULL )
                    mov rcx,[rcx].seg_item.next
                .endw
                mov [rcx].seg_item.next,rax
            .endif
        .endif

        .if ( i < TokenCount )

            .if ( [rbx].token != T_COMMA || [rbx+asm_tok].token == T_FINAL )
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif
            inc i
            add rbx,asm_tok
        .endif
    .until ( i >= TokenCount )
    .return( NOT_ERROR )

GrpDir endp


; get/set value of predefined symbol @WordSize

UpdateWordSize proc fastcall sym:asym_t, p:ptr

    mov [rcx].asym.value,CurrWordSize
    ret

UpdateWordSize endp


; called by SEGMENT and ENDS directives

SetOfssize proc

    mov rcx,CurrSeg
    .if ( rcx == NULL )

        mov MODULE.Ofssize,MODULE.defOfssize
    .else

        mov rax,[rcx].asym.seginfo
        movzx ecx,[rax].seg_info.Ofssize
        mov MODULE.Ofssize,cl
        lea rax,min_cpu
        movzx eax,word ptr [rax+rcx*2]

        .if ( MODULE.curr_cpu < eax )

            mov eax,16
            shl eax,cl
            .return( asmerr( 2066, eax ) )
        .endif
    .endif
    mov eax,2
    mov cl,MODULE.Ofssize
    shl eax,cl
    mov CurrWordSize,al
    xor eax,eax
    mov MODULE.accumulator,T_AX
    .if ( cl == USE64 )
        inc eax
        mov MODULE.accumulator,T_RAX
    .elseif ( cl == USE32 )
        mov MODULE.accumulator,T_EAX
    .endif
    Set64Bit( eax )
   .return( NOT_ERROR )

SetOfssize endp


; close segment

CloseSeg proc fastcall private uses rsi rdi sname:string_t

    mov rsi,rcx
    mov rcx,CurrSeg
    xor edi,edi
    .if ( rcx == NULL )
        inc edi
    .elseif ( SymCmpFunc( [rcx].asym.name, rsi, [rcx].asym.name_size ) != 0 )
        inc edi
    .endif
    .if ( edi )
        .return( asmerr( 1010, rsi ) )
    .endif
ifndef ASMC64
    .if ( write_to_file && ( Options.output_format == OFORMAT_OMF ) )
        omf_FlushCurrSeg()
        .if ( Options.no_comment_in_code_rec == FALSE )
            omf_OutSelect( FALSE )
        .endif
    .endif
endif
    pop_seg()
   .return( NOT_ERROR )

CloseSeg endp


DefineFlatGroup proc

    mov rax,MODULE.flat_grp
    .if ( rax == NULL )

        ; can't fail because <FLAT> is a reserved word

        mov MODULE.flat_grp,CreateGroup( "FLAT" )
        mov cl,MODULE.defOfssize
        mov [rax].asym.Ofssize,cl
    .endif
    mov [rax].asym.isdefined,1 ; v2.09
    ret

DefineFlatGroup endp


GetSegIdx proc fastcall sym:asym_t

    ; get idx to sym's segment

    mov rax,rcx
    .if ( rax )
        mov rax,[rax].asym.seginfo
        .return( [rax].seg_info.seg_idx )
    .endif
    ret

GetSegIdx endp


GetGroup proc fastcall sym:asym_t

    ; get a symbol's group

    .if ( GetSegm( rcx ) != NULL )

        mov rax,[rax].asym.seginfo
       .return( [rax].seg_info.sgroup )
    .endif
    ret

GetGroup endp


GetSymOfssize proc fastcall sym:asym_t

    ; get sym's offset size (64=2, 32=1, 16=0)

    .if ( GetSegm( rcx ) == NULL )

        mov rax,rcx
        .if ( [rax].asym.state == SYM_EXTERNAL )

            movzx eax,[rax].asym.segoffsize
           .return
        .endif

        .if ( [rax].asym.state == SYM_STACK || [rax].asym.state == SYM_GRP )
            .return( [rax].asym.Ofssize )
        .endif
        .if ( [rax].asym.state == SYM_SEG  )
            mov rax,[rax].asym.seginfo
            .return( [rax].seg_info.Ofssize )
        .endif

        ; v2.07: added

        .if ( [rax].asym.mem_type == MT_EMPTY )
            .return( USE16 )
        .endif
    .else
        mov rax,[rax].asym.seginfo
       .return( [rax].seg_info.Ofssize )
    .endif
    movzx eax,MODULE.Ofssize
    ret

GetSymOfssize endp


SetSymSegOfs proc fastcall sym:asym_t

    mov [rcx].asym.segm,CurrSeg
    mov [rcx].asym.offs,GetCurrOffset()
    ret

SetSymSegOfs endp


; get segment type from alignment, combine type or class name

TypeFromClassName proc fastcall uses rsi rdi s:asym_t, clname:asym_t

  local uname[MAX_ID_LEN+1]:char_t

    mov rax,[rcx].asym.seginfo
    .if ( [rax].seg_info.alignment == MAX_SEGALIGNMENT )
        .return( SEGTYPE_ABS )
    .endif

    ; v2.03: added
    .if ( [rax].seg_info.combine == COMB_STACK )
        .return( SEGTYPE_STACK )
    .endif

    .if ( rdx == NULL )
        .return( SEGTYPE_UNDEF )
    .endif

    mov rdi,rdx
    .ifd ( tstricmp( [rdi].asym.name, GetCodeClass() ) == 0 )
        .return( SEGTYPE_CODE )
    .endif

    mov esi,[rdi].asym.name_size
    lea ecx,[rsi+1]
    mov rdi,tstrupr( tmemcpy( &uname, [rdi].asym.name, ecx ) )

    .switch( esi )
    .case 5
        .ifd ( tmemcmp( rdi, "CONST", 6 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
        .ifd ( tmemcmp( rdi, "DBTYP", 6 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
        .ifd ( tmemcmp( rdi, "DBSYM", 6 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
    .case 4
        .ifd ( tmemcmp( &[rdi+rsi-4], "CODE", 4 ) == 0 )
            .return( SEGTYPE_CODE )
        .endif
        .ifd ( tmemcmp( &[rdi+rsi-4], "DATA", 4 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
    .case 3
        .ifd ( tmemcmp( &[rdi+rsi-3], "BSS", 3 ) == 0 )
            .return( SEGTYPE_BSS )
        .endif
        .endc
    .default
        .gotosw(5)
    .endsw
    .return( SEGTYPE_UNDEF )

TypeFromClassName endp


; search a class item by name.
; the classes aren't stored in the symbol table!

FindClass proc fastcall private uses rsi rdi rbx classname:string_t, len:int_t

    .for ( rbx = rcx, esi = edx,
           rdi = MODULE.LnameQueue.head : rdi : rdi = [rdi].qnode.next )

        mov rcx,[rdi].qnode.sym
        .if ( [rcx].asym.state == SYM_CLASS_LNAME )

            .if ( SymCmpFunc( [rcx].asym.name, rbx, esi ) == 0 )
                .return( [rdi].qnode.sym )
            .endif
        .endif
    .endf
    .return( NULL )

FindClass endp


; add a class name to the lname queue
; if it doesn't exist yet.

CreateClassLname proc fastcall private uses rsi rdi rbx name:string_t

    mov rbx,rcx
    mov esi,tstrlen( rcx )

    ; max lname is 255 - this is an OMF restriction

    .if ( esi > MAX_LNAME )

        asmerr( 2041 )
       .return( NULL )
    .endif

    .if !FindClass( rbx, esi )

        ; the classes aren't inserted into the symbol table
        ; but they are in a queue

        mov rsi,SymAlloc( rbx )
        mov [rsi].asym.state,SYM_CLASS_LNAME
        AddLnameItem( rsi )
        mov rax,rsi
    .endif
    ret

CreateClassLname endp


; set the segment's class. report an error if the class has been set
; already and the new value differs.

SetSegmentClass proc fastcall private uses rsi s:asym_t, name:string_t

    mov rsi,rcx
    .if ( CreateClassLname( rdx ) == NULL )
        .return( ERROR )
    .endif

    mov rcx,[rsi].asym.seginfo
    mov [rcx].seg_info.clsym,rax
   .return( NOT_ERROR )

SetSegmentClass endp


; CreateIntSegment(), used for internally defined segments:
; codeview debugging segments, COFF .drectve, COFF .sxdata

CreateIntSegment proc __ccall uses rdi name:string_t, classname:string_t, alignment:byte, Ofssize:byte, add_global:int_t

    .if ( add_global )

        SymSearch( name )
        .if ( rax == NULL || [rax].asym.state == SYM_UNDEFINED )
            CreateSegment( rax, name, add_global )
        .elseif ( [rax].asym.state != SYM_SEG )
            asmerr( 2005, name )
            .return( NULL )
        .endif
    .else
        CreateSegment( NULL, name, FALSE )
    .endif

    .if ( rax )
        mov rdi,rax
        .if ( !( [rdi].asym.isdefined ) )

            inc MODULE.num_segs
            mov rcx,[rdi].asym.seginfo
            mov [rcx].seg_info.seg_idx,MODULE.num_segs
            AddLnameItem( rdi )
            mov [rdi].asym.isdefined,1 ; v2.12: added
        .endif
        mov rcx,[rdi].asym.seginfo
        mov [rcx].seg_info.internal,1 ; segment has private buffer
        mov [rdi].asym.segm,rdi
        mov [rcx].seg_info.alignment,alignment
        mov [rcx].seg_info.Ofssize,Ofssize
        SetSegmentClass( rdi, classname )
        .return( rdi )
    .endif
    ret

CreateIntSegment endp


; ENDS directive

EndsDir proc __ccall uses rbx i:int_t, tokenarray:token_t

    ldr rbx,tokenarray
    .if ( CurrStruct != NULL )
        .return( EndstructDirective( i, rbx ) )
    .endif
    ; a label must precede ENDS
    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [rbx+rcx].string_ptr ) )
    .endif
    .if ( Parse_Pass != PASS_1 )
        .if ( MODULE.list )
            LstWrite( LSTTYPE_LABEL, 0, NULL )
        .endif
    .endif
    .ifd ( CloseSeg( [rbx].string_ptr ) == ERROR )
        .return( ERROR )
    .endif
    inc i
    imul ecx,i,asm_tok
    .if ( [rbx+rcx].token != T_FINAL )
        asmerr( 2008, [rbx+rcx].string_ptr )
    .endif
    .return( SetOfssize() )

EndsDir endp


; SEGMENT directive if pass is > 1

SetCurrSeg proc fastcall private uses rdi rbx i:int_t, tokenarray:token_t

    mov rbx,rdx
    mov rdi,SymSearch( [rbx].string_ptr )
    .if ( rdi == NULL || [rdi].asym.state != SYM_SEG )
        .return( asmerr( 2006, [rbx].string_ptr ) )
    .endif

    ; v2.04: added

    mov [rdi].asym.isdefined,1
ifndef ASMC64
    .if ( CurrSeg && Options.output_format == OFORMAT_OMF )

        omf_FlushCurrSeg()

        .if ( Options.no_comment_in_code_rec == FALSE )
            omf_OutSelect( FALSE )
        .endif
    .endif
endif
    push_seg( rdi )
    mov ebx,SetOfssize() ; v2.18: set offset size BEFORE listing, so it shows correctly

    .if ( MODULE.list )

        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif
    .return( ebx )

SetCurrSeg endp


UnlinkSeg proc fastcall private uses rdi dir:asym_t

    .for ( rdx = SymTables[TAB_SEG*symbol_queue].head, rdi = NULL : rdx : rdi = rdx, rdx = [rdx].asym.next )

        .if ( rdx == rcx )

            ; if segment is first, set a new head

            .if ( rdi == NULL )
                mov SymTables[TAB_SEG*symbol_queue].head,[rdx].asym.next
            .else
                mov [rdi].asym.next,[rdx].asym.next
            .endif

            ; if segment is last, set a new tail

            .if ( [rdx].asym.next == NULL )
                mov SymTables[TAB_SEG*symbol_queue].tail,rdi
            .endif
        .endif
    .endf
    ret

UnlinkSeg endp


; SEGMENT directive

SegmentDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new is_old:char_t = FALSE
   .new token:string_t
   .new typeidx:int_t
   .new type:ptr typeinfo      ; type of option
   .new newseg:int_t = 0
   .new temp:int_t
   .new temp2:int_t
   .new initstate:dword = 0    ; flags for attribute initialization
   .new oldOfssize:uchar_t
   .new oldalign:char_t
   .new oldcombine:char_t
   .new newcharacteristics:uint_8 = 0
   .new dir:asym_t
   .new name:string_t
   .new sym:asym_t
   .new opndx:expr

    ldr rbx,tokenarray
    .if ( Parse_Pass != PASS_1 )
        .return( SetCurrSeg( i, rbx ) )
    .endif

    .if ( i != 1 )

        imul ecx,i,asm_tok
       .return( asmerr( 2008, [rbx+rcx].string_ptr ) )
    .endif

    mov name,[rbx].string_ptr

    ; See if the segment is already defined
    mov sym,SymSearch( name )

    .if ( rax == NULL || [rax].asym.state == SYM_UNDEFINED )

        mov newseg,1

        ; segment is not defined (yet)

        mov sym,CreateSegment( sym, name, TRUE )
        mov [rax].asym.list,1 ; always list segments
        mov dir,rax
        mov oldOfssize,USE_EMPTY ; v2.13: added

    .elseif ( [rax].asym.state == SYM_SEG ) ; segment already defined?

        mov dir,rax
        mov rdi,rax

        .if ( !( [rax].asym.isdefined ) )

            ; segment was forward referenced (in a GROUP directive), but not really set up
            ; the segment list is to be sorted.
            ; So unlink the segment and add it at the end.

            UnlinkSeg( rdi )
            mov [rdi].asym.next,NULL
            .if ( SymTables[TAB_SEG*symbol_queue].head == NULL )

                mov SymTables[TAB_SEG*symbol_queue].head,rdi
                mov SymTables[TAB_SEG*symbol_queue].tail,rdi
            .else
                mov rcx,SymTables[TAB_SEG*symbol_queue].tail
                mov [rcx].asym.next,rdi
                mov SymTables[TAB_SEG*symbol_queue].tail,rdi
            .endif
            mov rcx,[rdi].asym.seginfo
            mov oldOfssize,[rcx].seg_info.Ofssize ; v2.13: check segment's word size

            ; v2.14: set a default ofsset size

            .if ( al == USE_EMPTY )
                mov [rcx].seg_info.Ofssize,MODULE.Ofssize
            .endif
        .else

            mov is_old,TRUE
            mov rcx,[rdi].asym.seginfo
            mov oldOfssize,  [rcx].seg_info.Ofssize
            mov oldalign,    [rcx].seg_info.alignment
            mov oldcombine,  [rcx].seg_info.combine
        .endif

    .else

        ; symbol is different kind, error

        .return( asmerr( 2005, name ) )
    .endif

    inc i ; go past SEGMENT

    .for ( : i < TokenCount: i++ )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        mov rsi,[rbx].string_ptr
        .if ( [rbx].token == T_STRING )

            ; the class name - the only token which is of type STRING
            ; string must be delimited by [double]quotes

            .if ( [rbx].string_delim != '"' && [rbx].string_delim != "'" )

                asmerr( 2008, rsi )
               .continue
            .endif

            ; remove the quote delimiters

            inc rsi
            mov ecx,[rbx].stringlen
            mov byte ptr [rsi+rcx],NULLC

            SetSegmentClass( dir, rsi )
           .continue
        .endif

        ; check the rest of segment attributes.

        mov typeidx,FindToken( rsi, &SegAttrToken, count_SegAttrToken )
        .if ( typeidx < 0 )

            asmerr( 2015, rsi, "attributes" )
           .continue
        .endif
        lea rcx,SegAttrValue
        mov type,&[rcx+rax*typeinfo]

        ; initstate is used to check if any field is already
        ; initialized

        movzx edx,[rax].typeinfo.init
        mov ecx,initstate
        mov eax,edx
        and eax,INIT_EXCL_MASK
        and eax,ecx

        .if ( eax )

            asmerr( 2015, rsi, "attributes" )
           .continue
        .endif

        or initstate,edx ; mark it initialized
        mov rcx,dir
        mov rdi,[rcx].asym.seginfo
        mov rcx,type

        .switch ( edx )
        .case INIT_ATTR
            mov [rdi].seg_info.readonly,1
           .endc
        .case INIT_ALIGN
            mov [rdi].seg_info.alignment,[rcx].typeinfo.value
           .endc
        .case INIT_ALIGN_PARAM
            .if ( Options.output_format == OFORMAT_OMF )
                asmerr( 3006, [rbx].string_ptr )
                mov i,TokenCount ; stop further parsing of this line
               .endc
            .endif
            inc i
            add rbx,asm_tok
            .if ( [rbx].token != T_OP_BRACKET )
                asmerr( 2065, "(" )
               .endc
            .endif
            inc i
            EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 )
            .endc .ifd ( eax == ERROR )

            imul ebx,i,asm_tok
            add rbx,tokenarray

            ; v2.19: if format -bin, accept ALIGN(num,v) syntax

            .if ( Options.output_format == OFORMAT_BIN && MODULE.sub_format == SFORMAT_NONE && [rbx].token == T_COMMA )

                inc i
                add rbx,asm_tok
                mov rcx,[rbx].string_ptr
                movzx eax,word ptr [rcx]
                or al,0x20
                .if ( [rbx].token == T_ID && ax == 'v' )
                    inc i
                    add rbx,asm_tok
                    mov [rdi].seg_info.align_rva,1
                .else
                    asmerr( 2008, rcx )
                   .endc
                .endif
            .endif

            .if ( [rbx].token != T_CL_BRACKET )
                asmerr( 2065, ")" )
               .endc
            .endif

            .if ( opndx.kind != EXPR_CONST )

                asmerr( 2026 )
               .endc
            .endif

            ; COFF allows alignment values
            ; 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192

            .for ( ecx = 1, edx = 0: ecx < opndx.value && ecx < 8192 : ecx <<= 1, edx++ )
            .endf

            .if ( ecx != opndx.value )

                mov temp,edx
                asmerr( 2063, opndx.value )
                mov edx,temp
            .endif
            mov [rdi].seg_info.alignment,dl
           .endc
        .case INIT_COMBINE
            mov [rdi].seg_info.combine,[rcx].typeinfo.value
           .endc
        .case INIT_COMBINE_AT
            mov [rdi].seg_info.combine,[rcx].typeinfo.value
            mov [rdi].seg_info.alignment,MAX_SEGALIGNMENT
            inc i

            .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) != ERROR )
                .if ( opndx.kind == EXPR_CONST )
                    mov [rdi].seg_info.abs_frame,opndx.value
                    mov [rdi].seg_info.abs_offset,0
                .else
                    asmerr( 2026 )
                .endif
            .endif
            .endc
        .case INIT_COMBINE_COMDAT
            .if ( Options.output_format != OFORMAT_COFF && Options.output_format != OFORMAT_OMF )

                asmerr( 3006, [rbx].string_ptr )
                mov i,TokenCount ; stop further parsing of this line
               .endc
            .endif
            inc i
            add rbx,asm_tok
            .if ( [rbx].token != T_OP_BRACKET )

                asmerr( 2065, "(" )
               .endc
            .endif
            inc i
            .endc .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, 0 ) == ERROR )

            imul ebx,i,asm_tok
            add rbx,tokenarray

            .if ( opndx.kind != EXPR_CONST )

                asmerr( 2026 )
                mov i,TokenCount ; stop further parsing of this line
               .endc
            .endif

            .if ( opndx.value < 1 || opndx.value > 6 )
                asmerr( 2156, "1-6" )
            .else

                ; if value is IMAGE_COMDAT_SELECT_ASSOCIATIVE,
                ; get the associated segment name argument.

                .if ( opndx.value == 5 )

                    ;asym *sym2

                    .if ( [rbx].token != T_COMMA )

                        asmerr( 2008, [rbx].tokpos )
                        mov i,TokenCount ; stop further parsing of this line
                       .endc
                    .endif
                    inc i
                    add rbx,asm_tok
                    .if ( [rbx].token != T_ID )

                        asmerr(2008, [rbx].string_ptr )
                        mov i,TokenCount ; stop further parsing of this line
                       .endc
                    .endif

                    ; associated segment must be COMDAT, but not associative

                    .if SymSearch( [rbx].string_ptr )
                        mov rcx,[rax].asym.seginfo
                    .endif
                    .if ( rax == NULL || [rax].asym.state != SYM_SEG ||
                        [rcx].seg_info.comdatselection == 0 ||
                        [rcx].seg_info.comdatselection == 5 )
                        asmerr( 2008, [rbx].string_ptr )
                    .else
                        mov [rdi].seg_info.comdat_number,[rcx].seg_info.seg_idx
                    .endif
                    inc i
                    add rbx,asm_tok
                .endif
            .endif

            .if ( [rbx].token != T_CL_BRACKET )

                asmerr( 2065, ")" )
               .endc
            .endif
            mov [rdi].seg_info.comdatselection,opndx.value
            mov rcx,type
            mov [rdi].seg_info.combine,[rcx].typeinfo.value
           .endc
        .case INIT_OFSSIZE_FLAT
            .if ( MODULE.defOfssize == USE16 )

                asmerr( 2085 )
               .endc
            .endif

            DefineFlatGroup()

            ; v2.09: make sure ofssize is at least USE32 for FLAT
            ; v2.14: USE16 doesn't need to be handled here anymore

            mov [rdi].seg_info.Ofssize,MODULE.defOfssize

            ; put the segment into the FLAT group.
            ; this is not quite Masm-compatible, because trying to put
            ; the segment into another group will cause an error.

            mov [rdi].seg_info.sgroup,MODULE.flat_grp
           .endc
        .case INIT_OFSSIZE
            mov rcx,type
            mov [rdi].seg_info.Ofssize,[rcx].typeinfo.value

            ; v2.17: if .model FLAT, put USE64 segments into flat group.
            ; be aware that the "flat" attribute affects fixups of non-flat items for -pe format.

            .if ( [rcx].typeinfo.value == USE64 && MODULE._model == MODEL_FLAT )
                mov [rdi].seg_info.sgroup,MODULE.flat_grp
            .endif
            .endc
        .case INIT_CHAR_INFO
            mov [rdi].seg_info.information,1 ; fixme: check that this flag isn't changed
           .endc
        .case INIT_CHAR
            ; characteristics are restricted to COFF/ELF/BIN-PE
            .if ( Options.output_format == OFORMAT_OMF || ( Options.output_format == OFORMAT_BIN &&
                ( MODULE.sub_format != SFORMAT_PE && MODULE.sub_format != SFORMAT_64BIT ) ) )

                asmerr( 3006, [rbx].string_ptr )
            .else
                or newcharacteristics,[rcx].typeinfo.value
            .endif
            .endc
        .case INIT_ALIAS
            ; alias() is restricted to COFF/ELF/BIN-PE
            .if ( Options.output_format == OFORMAT_OMF || ( Options.output_format == OFORMAT_BIN &&
                ( MODULE.sub_format != SFORMAT_PE && MODULE.sub_format != SFORMAT_64BIT ) ) )
                asmerr( 3006, [rbx].string_ptr )
                mov i,TokenCount ; stop further parsing of this line
               .endc
            .endif
            inc i
            add rbx,asm_tok
            .if ( [rbx].token != T_OP_BRACKET )

                asmerr( 2065, "(" )
               .endc
            .endif
            inc i
            add rbx,asm_tok
            .if ( [rbx].token != T_STRING || ( [rbx].string_delim != '"' && [rbx].string_delim != "'" ) )

                asmerr(2008, token )
                mov i,TokenCount ; stop further parsing of this line
               .endc
            .endif
            mov rsi,rbx
            inc i
            add rbx,asm_tok
            .if ( [rbx].token != T_CL_BRACKET )
                asmerr( 2065, ")" )
               .endc
            .endif
            mov rbx,rsi

            ; v2.10: if segment already exists, check that old and new aliasname are equal

            .if ( is_old )

                .if ( [rdi].seg_info.aliasname )

                    mov esi,tstrlen( [rdi].seg_info.aliasname )
                    mov rcx,[rbx].string_ptr
                    inc rcx
                    tmemcmp( [rdi].seg_info.aliasname, rcx, [rbx].stringlen )
                .endif

                .if ( [rdi].seg_info.aliasname == NULL || ( [rbx].stringlen != esi ) || eax )

                    mov rcx,dir
                    asmerr( 2015, [rcx].asym.name, "alias" )
                   .endc
                .endif

            .else

                ; v2.10: " + 1" was missing in next line

                mov ecx,[rbx].stringlen
                inc ecx
                mov [rdi].seg_info.aliasname,LclAlloc( ecx )
                mov rcx,[rbx].string_ptr
                inc rcx
                mov esi,[rbx].stringlen
                tmemcpy( [rdi].seg_info.aliasname, rcx, esi )
                mov byte ptr [rax+rsi],NULLC
            .endif
            .endc
        .endsw
    .endf

    ; make a guess about the segment's type

    mov rcx,dir
    mov rdi,[rcx].asym.seginfo

    .if ( [rdi].seg_info.segtype != SEGTYPE_CODE )

        TypeFromClassName( dir, [rdi].seg_info.clsym )
        .if ( eax != SEGTYPE_UNDEF )
            mov [rdi].seg_info.segtype,eax
        .endif
    .endif

    .if ( is_old )

        xor esi,esi

        ; Check if new definition is different from previous one

        .if ( oldalign != [rdi].seg_info.alignment )
            lea rsi,@CStr("alignment")
        .elseif ( oldcombine != [rdi].seg_info.combine )
            lea rsi,@CStr("combine")
        .elseif ( oldOfssize != [rdi].seg_info.Ofssize )
            lea rsi,@CStr("segment word size")
        .elseif ( newcharacteristics && ( newcharacteristics != [rdi].seg_info.characteristics ) )
            lea rsi,@CStr("characteristics")
        .endif

        .if ( rsi )
            mov rcx,dir
            asmerr( 2015, [rcx].asym.name, rsi )
        .endif

    .else

        ; A new definition

        mov rcx,sym
        mov [rcx].asym.isdefined,1
        mov [rcx].asym.segm,rcx
        mov [rcx].asym.offs,0 ; remains 0 ( =segment's local start offset )

if 1    ; v2.34.61

        ; v2.13: check segment's word size. This is mainly for segment forward
        ; refs in GROUP directives. If this check is missing, one can mix segments
        ; in a group by adding segments BEFORE they were defined.

        mov al,oldOfssize
        .if ( al != USE_EMPTY && al != [rdi].seg_info.Ofssize )

            asmerr( 2015, [rcx].asym.name, "segment word size" )

        .else  ; v2.14: else-block added

            mov rdx,[rdi].seg_info.sgroup
            .if ( rdx )

                .if ( [rdx].asym.Ofssize == USE_EMPTY )

                    mov [rdx].asym.Ofssize,[rdi].seg_info.Ofssize

                .elseif ( [rdx].asym.Ofssize != [rdi].seg_info.Ofssize )

                    .if ( rdx == MODULE.flat_grp && [rdi].seg_info.Ofssize >= USE32 )
                        ; v2.17: allow both 32- and 64-bit segments in FLAT group
                    .else
                        asmerr( 2015, [rcx].asym.name, "segment word size" )
                    .endif
                .endif
            .endif
        .endif
endif
        ; no segment index for COMDAT segments in OMF!

        .if ( [rdi].seg_info.comdatselection && Options.output_format == OFORMAT_OMF )

        .else
            inc MODULE.num_segs
            mov [rdi].seg_info.seg_idx,MODULE.num_segs
            AddLnameItem( sym )
        .endif

    .endif
    .if ( newcharacteristics )
        mov [rdi].seg_info.characteristics,newcharacteristics
    .endif

    push_seg( dir ) ; set CurrSeg

    mov esi,SetOfssize()

    .if ( newseg && [rdi].seg_info.segtype == SEGTYPE_CODE )

        .if ( Options.debug_symbols == 4 && CV8Label == NULL )
            mov CV8Label,CreateLabel( "$$000000", 0, 0, 0 )
        .endif

        .if ( !ImageBase && Options.output_format == OFORMAT_BIN && Options.sub_format != SFORMAT_NONE )

            .new ti:qualified_type
            .if !SymFind("IMAGE_DOS_HEADER")
               SymCreate("IMAGE_DOS_HEADER")
            .endif
            mov ti.symtype,rax
            CreateLabel( "__ImageBase", MT_TYPE, &ti, 0 )
            mov [rax].asym.offs,-0x1000
            inc ImageBase
        .endif
    .endif
    .if ( MODULE.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif
    .return( esi )

SegmentDir endp


; sort segments ( a simple bubble sort )
; type,0: sort by fileoffset (.DOSSEG )
; type,1: sort by name ( .ALPHA )
; type,2: sort by segment type+name ( PE format ). member lname_idx is misused here for "type"

    assume rbx:nothing

SortSegments proc __ccall uses rsi rdi rbx type:int_t

    .new changed:int_t = TRUE
    .new swap:int_t
    .new curr:asym_t
    .new index:int_t = 1

    .while ( changed == TRUE )

        xor esi,esi
        mov changed,FALSE

        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head: rdi && [rdi].asym.next : rsi = rdi, rdi = [rdi].asym.next )

            mov swap,FALSE
            mov rbx,[rdi].asym.seginfo

            .switch (type )
            .case 0
                mov rcx,[rdi].asym.next
                mov rcx,[rcx].asym.seginfo
                .if ( [rbx].seg_info.fileoffset > [rcx].seg_info.fileoffset )
                    mov swap,TRUE
                .endif
                .endc
            .case 1
                mov rcx,[rdi].asym.next
                .ifsd ( tstrcmp( [rdi].asym.name, [rcx].asym.name ) > 0 )
                    mov swap,TRUE
                .endif
                .endc
            .case 2
                mov rdx,[rdi].asym.next
                mov rcx,[rdx].asym.seginfo
                .if ( [rbx].seg_info.lname_idx > [rcx].seg_info.lname_idx )
                    mov swap,TRUE
                .elseif ( [rbx].seg_info.lname_idx == [rcx].seg_info.lname_idx )
                    .ifsd ( tstricmp( [rdi].asym.name, [rdx].asym.name ) > 0 )
                        mov swap,TRUE
                    .endif
                .endif
                .endc
            .endsw
            .if ( swap )
                mov rdx,[rdi].asym.next
                mov changed,TRUE
                .if ( rsi == NULL )
                    mov SymTables[TAB_SEG*symbol_queue].head,rdx
                .else
                    mov [rsi].asym.next,rdx
                .endif
                mov [rdi].asym.next,[rdx].asym.next
                mov [rdx].asym.next,rdi
            .endif
        .endf
    .endw
    ret

SortSegments endp


; END directive has been found.

SegmentModuleExit proc uses rdi

    .if ( MODULE._model != MODEL_NONE )
        ModelSimSegmExit()
    .endif

    ; if there's still an open segment, it's an error
    mov rdi,CurrSeg
    .if ( rdi )
        asmerr( 1010, [rdi].asym.name )

        ; but close the still open segments anyway

        .while ( rdi )
            .break .ifd ( CloseSeg( [rdi].asym.name ) != NOT_ERROR )
            mov rdi,CurrSeg
        .endw
    .endif
    .return( NOT_ERROR )

SegmentModuleExit endp


; this is called once per module after the last pass is finished

SegmentFini proc

    FreeLnameQueue()
    ret

SegmentFini endp


; init. called for each pass

SegmentInit proc fastcall uses rsi rdi pass:int_t

   .new curr:asym_t
   .new i:uint_32
   .new p:string_t

    mov CurrSeg,NULL
    mov stkindex,0

    .if ( ecx == PASS_1 )

        mov grpdefidx,0
        mov buffer_size,0
        mov CV8Label,NULL
    .endif

    ; alloc a buffer for the contents

    .if ( MODULE.pCodeBuff == NULL && Options.output_format != OFORMAT_OMF )

        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head,
                buffer_size = 0: rdi: rdi = [rdi].asym.next )

            mov rcx,[rdi].asym.seginfo

            .if ( [rcx].seg_info.internal )
                .continue
            .endif

            .if ( [rcx].seg_info.bytes_written )

                mov eax,[rdi].asym.max_offset
                sub eax,[rcx].seg_info.start_loc

                ; the segment can grow in step 2-n due to forward references.
                ; for a quick solution just add 25% to the size if segment
                ; is a code segment. (v2.02: previously if was added only if
                ; code segment contained labels, but this isn't sufficient.)

                .if ( [rcx].seg_info.segtype == SEGTYPE_CODE )

                    mov edx,eax
                    shr eax,2
                    add eax,edx
                .endif
                add buffer_size,eax
            .endif
        .endf

        .if ( buffer_size )
            mov MODULE.pCodeBuff,LclAlloc( buffer_size )
        .endif
    .endif

    ; Reset length of all segments to zero.
    ; set start of segment buffers.

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head,
           rsi = MODULE.pCodeBuff: rdi: rdi = [rdi].asym.next )

        mov rcx,[rdi].asym.seginfo
        mov [rcx].seg_info.current_loc,0
        .continue .if ( [rcx].seg_info.internal )

        .if ( [rcx].seg_info.bytes_written )

            .if ( Options.output_format == OFORMAT_OMF )
                mov [rcx].seg_info.CodeBuffer,&codebuf
            .else
                mov [rcx].seg_info.CodeBuffer,rsi
                mov eax,[rdi].asym.max_offset
                sub eax,[rcx].seg_info.start_loc
                add rsi,rax
            .endif
        .endif

        .if ( [rcx].seg_info.combine != COMB_STACK )
            mov [rdi].asym.max_offset,0
        .endif

        .if ( Options.output_format == OFORMAT_OMF )  ;; v2.03: do this selectively

            mov [rcx].seg_info.start_loc,0
            mov [rcx].seg_info.data_in_code,0
        .endif

        mov [rcx].seg_info.bytes_written,0
        mov [rcx].seg_info.head,NULL
        mov [rcx].seg_info.tail,NULL
    .endf

    mov MODULE.Ofssize,USE16
    .if ( UseSavedState == TRUE )

        mov CurrSeg,saved_CurrSeg
        mov stkindex,saved_stkindex

        .if ( stkindex )

            imul ecx,stkindex,sizeof(asym_t)
            tmemcpy( &SegStack, saved_SegStack, ecx )
        .endif
        UpdateCurrSegVars()
    .endif
    ret

SegmentInit endp


SegmentSaveState proc

    mov saved_CurrSeg,CurrSeg
    mov saved_stkindex,stkindex

    .if ( stkindex )

        imul ecx,stkindex,sizeof(asym_t)
        mov saved_SegStack,LclAlloc( ecx )
        imul ecx,stkindex,sizeof(asym_t)
        tmemcpy( saved_SegStack, &SegStack, ecx )
    .endif
    ret

SegmentSaveState endp

    end
