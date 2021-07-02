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

EndstructDirective proto :int_t, :ptr asm_tok

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


grpdefidx   dd 0    ; Number of group definitions
SegStack    dsym_t MAX_SEG_NESTING dup(0) ; stack of open segments
stkindex    int_t 0 ; current top of stack

; saved state
saved_CurrSeg   dsym_t 0
saved_SegStack  ptr dsym_t 0
saved_stkindex  int_t 0

; generic byte buffer, used for OMF LEDATA records only
codebuf         db 1024 dup(0)
buffer_size     dd 0 ; total size of code buffer

; min cpu for USE16, USE32 and USE64
min_cpu         dw P_86, P_386, P_64

.code

; find token in a string table

FindToken proc private uses esi edi token:string_t, table:ptr, size:int_t

    mov esi,table
    .for ( edi = 0 : edi < size : edi++ )
        lodsd
        .if ( _stricmp( eax, token ) == 0 )
            .return( edi )
        .endif
    .endf
    .return( -1 ) ; Not found

FindToken endp

; set value of $ symbol

UpdateCurPC proc sym:ptr asym, p:ptr

    mov ecx,sym
    mov edx,CurrStruct
    .if ( edx )
        mov [ecx].asym.mem_type,MT_EMPTY
        mov [ecx].asym.segm,NULL ; v2.07: needed again
        mov eax,[edx].asym.offs
        .if [edx].dsym.next
            mov edx,[edx].dsym.next
            add eax,[edx].asym.offs
        .endif
        mov [ecx].asym.offs,eax
    .elseif ( CurrSeg )  ; v2.10: check for CurrSeg != NULL
        mov [ecx].asym.mem_type,MT_NEAR
        mov [ecx].asym.segm,CurrSeg
        mov [ecx].asym.offs,GetCurrOffset()
    .else
        asmerr( 2034 ) ; v2.10: added
    .endif
    ret

UpdateCurPC endp

AddLnameItem proc private sym:ptr asym
    QAddItem( &ModuleInfo.LnameQueue, sym )
    ret
AddLnameItem endp

; what's inserted into the LNAMES queue:
; SYM_SEG: segment names
; SYM_GRP: group names
; SYM_CLASS_LNAME : class names

FreeLnameQueue proc private uses esi edi

    .for ( edi = ModuleInfo.LnameQueue.head: edi: edi = esi )
        mov esi,[edi].qnode.next

        ; the class name symbols are not part of the
        ; symbol table and hence must be freed now.
        mov ecx,[edi].qnode.sym
        .if ( [ecx].asym.state == SYM_CLASS_LNAME )
            SymFree( ecx )
        .endif
    .endf
    ret

FreeLnameQueue endp

; set CS assume entry whenever current segment is changed.
; Also updates values of text macro @CurSeg.

UpdateCurrSegVars proc private uses esi edi

    mov ecx,symCurSeg
    mov edi,CurrSeg
    lea esi,SegAssumeTable[ASSUME_CS*8]
    .if ( edi == NULL )
        mov [esi].assume_info.symbol,NULL
        mov [esi].assume_info.is_flat,FALSE
        mov [esi].assume_info.error,TRUE
        mov [ecx].asym.string_ptr,&@CStr("")
    .else
        mov [esi].assume_info.is_flat,FALSE
        mov [esi].assume_info.error,FALSE
        ; fixme: OPTION OFFSET:SEGMENT?
        mov edx,[edi].dsym.seginfo
        .if ( [edx].seg_info.sgroup != NULL )
            mov [esi].assume_info.symbol,[edx].seg_info.sgroup
            .if ( eax == ModuleInfo.flat_grp )
                mov [esi].assume_info.is_flat,TRUE
            .endif
        .else
            mov [esi].assume_info.symbol,edi
        .endif
        mov [ecx].asym.string_ptr,[edi].asym.name
    .endif
    ret

UpdateCurrSegVars endp

push_seg proc fastcall private s:ptr dsym

    ; Push a segment into the current segment stack

    mov edx,stkindex
    .if ( edx >= MAX_SEG_NESTING )
        .return asmerr( 1007 )
    .endif
    inc stkindex
    mov SegStack[edx*4],CurrSeg
    mov CurrSeg,ecx
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
        mov CurrSeg,SegStack[ecx*4]
        UpdateCurrSegVars()
    .endif
    ret

pop_seg endp

GetCurrOffset proc

    mov eax,CurrSeg
    .if eax
        mov eax,[eax].dsym.seginfo
        mov eax,[eax].seg_info.current_loc
    .endif
    ret

GetCurrOffset endp

GetCurrSegAlign proc

    mov eax,CurrSeg
    .return .if ( eax == NULL )

    mov ecx,[eax].dsym.seginfo
    .if ( [ecx].seg_info.alignment == MAX_SEGALIGNMENT ) ; ABS?
        .return( 0x10 ) ; assume PARA alignment for AT segments
    .endif
    mov cl,[ecx].seg_info.alignment
    mov eax,1
    shl eax,cl
    ret

GetCurrSegAlign endp

CreateGroup proc private uses edi name:string_t

    mov edi,SymSearch( name )

    .if ( edi == NULL || [edi].asym.state == SYM_UNDEFINED )
        .if ( edi == NULL )
            mov edi,SymCreate( name )
        .else
            sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], edi )
        .endif

        mov [edi].asym.state,SYM_GRP
        mov [edi].dsym.grpinfo,LclAlloc( sizeof( grp_info ) )
        mov [eax].grp_info.seglist,NULL
        mov [eax].grp_info.numseg,0
        sym_add_table( &SymTables[TAB_GRP*symbol_queue], edi )

        or  [edi].asym.flag1,S_LIST
        mov ecx,[edi].dsym.grpinfo
        inc grpdefidx
        mov [ecx].grp_info.grp_idx,grpdefidx
        AddLnameItem( edi )
    .elseif( [edi].asym.state != SYM_GRP )
        asmerr( 2005, name )
        .return( NULL )
    .endif
    or [edi].asym.flags,S_ISDEFINED
    .return( edi )

CreateGroup endp

CreateSegment proc private uses edi s:ptr dsym, name:string_t, add_global:int_t

    mov edi,s
    .if ( edi == NULL )
        .if ( add_global )
            SymCreate( name )
        .else
            SymAlloc( name )
        .endif
        mov edi,eax
    .elseif ( [edi].asym.state == SYM_UNDEFINED )
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], edi )
    .endif

    .if ( edi )
        mov [edi].asym.state,SYM_SEG
        mov [edi].dsym.seginfo,LclAlloc( sizeof( seg_info ) )
        mov ecx,memset( eax, 0, sizeof( seg_info ) )
        mov [ecx].seg_info.Ofssize,ModuleInfo.defOfssize
        mov [ecx].seg_info.alignment,4 ; this is PARA (2^4)
        mov [ecx].seg_info.combine,COMB_INVALID

        ; null class name, in case none is mentioned

        mov [edi].dsym.next,NULL

        ; don't use sym_add_table(). Thus the "prev" member
        ; becomes free for another use.

        .if ( SymTables[TAB_SEG*symbol_queue].head == NULL )
            mov SymTables[TAB_SEG*symbol_queue].head,edi
            mov SymTables[TAB_SEG*symbol_queue].tail,edi
        .else
            mov ecx,SymTables[TAB_SEG*symbol_queue].tail
            mov [ecx].dsym.next,edi
            mov SymTables[TAB_SEG*symbol_queue].tail,edi
        .endif
    .endif
    .return( edi )

CreateSegment endp

; handle GROUP directive

    assume ebx:ptr asm_tok

GrpDir proc uses esi esi edi i:int_t, tokenarray:ptr asm_tok

  local name:string_t

    ; GROUP directive must be at pos 1, needs a name at pos 0

    mov ebx,tokenarray
    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [ebx+ecx].string_ptr ) )
    .endif

    ; GROUP isn't valid for COFF/ELF/BIN-PE

    .if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF || \
        ( Options.output_format == OFORMAT_BIN && ModuleInfo.sub_format == SFORMAT_PE ) )
        .return( asmerr( 2214 ) )
    .endif
    mov edi,CreateGroup( [ebx].string_ptr )
    .if ( edi == NULL )
        .return( ERROR )
    .endif

    inc i ; go past GROUP
    add ebx,asm_tok*2

    .repeat

        ; get segment name
        .if ( [ebx].token != T_ID )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        mov name,[ebx].string_ptr
        inc i
        add ebx,asm_tok

        mov esi,SymSearch( name )
        .if ( Parse_Pass == PASS_1 )
            .if ( esi )
                mov ecx,[esi].dsym.seginfo
            .endif

            .if ( esi == NULL || [esi].asym.state == SYM_UNDEFINED )

                mov esi,CreateSegment( esi, name, TRUE )

                ; inherit the offset magnitude from the group
                mov edx,[edi].dsym.grpinfo
                .if ( [edx].grp_info.seglist )
                    mov ecx,[esi].dsym.seginfo
                    mov [ecx].seg_info.Ofssize,[edi].asym.Ofssize
                .endif

            .elseif ( [esi].asym.state != SYM_SEG )

                .return( asmerr( 2097, name ) )

                ; v2.09: allow segments in FLAT magic group be moved to a "real" group

            .elseif ( [ecx].seg_info.sgroup != NULL && \
                      [ecx].seg_info.sgroup != ModuleInfo.flat_grp && \
                      [ecx].seg_info.sgroup != edi )
                ; segment is in another group
                .return( asmerr( 2072, name ) )
            .endif

            ; the first segment will define the group's word size

            mov edx,[edi].dsym.grpinfo
            mov ecx,[esi].dsym.seginfo
            .if ( [edx].grp_info.seglist == NULL )
                mov [edi].asym.Ofssize,[ecx].seg_info.Ofssize
            .elseif ( [edi].asym.Ofssize != [ecx].seg_info.Ofssize )
                .return( asmerr( 2100, [edi].asym.name, [esi].asym.name ) )
            .endif
        .else
            .if ( esi == NULL || [esi].asym.state != SYM_SEG || [esi].asym.segm == NULL )
                .return( asmerr( 2006, name ) )
            .endif
        .endif

        ; insert segment in group if it's not there already

        mov ecx,[esi].dsym.seginfo
        .if ( [ecx].seg_info.sgroup == NULL )

            ; set the segment's grp

            mov [ecx].seg_info.sgroup,edi

            LclAlloc( sizeof( seg_item ) )
            mov [eax].seg_item.iseg,esi
            mov [eax].seg_item.next,NULL
            mov edx,[edi].dsym.grpinfo
            inc [edx].grp_info.numseg

            ; insert the segment at the end of linked list

            .if ( [edx].grp_info.seglist == NULL )
                mov [edx].grp_info.seglist,eax
            .else
                mov ecx,[edx].grp_info.seglist
                .while ( [ecx].seg_item.next != NULL )
                    mov ecx,[ecx].seg_item.next
                .endw
                mov [ecx].seg_item.next,eax
            .endif
        .endif

        .if ( i < Token_Count )
            .if ( [ebx].token != T_COMMA || [ebx+16].token == T_FINAL )
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif
            inc i
            add ebx,asm_tok
        .endif
    .until ( i >= Token_Count )
    .return( NOT_ERROR )

GrpDir endp

; get/set value of predefined symbol @WordSize

UpdateWordSize proc sym:ptr asym, p:ptr

    mov ecx,sym
    mov [ecx].asym.value,CurrWordSize
    ret

UpdateWordSize endp


; called by SEGMENT and ENDS directives

SetOfssize proc

    mov ecx,CurrSeg
    .if ( ecx == NULL )
        mov ModuleInfo.Ofssize,ModuleInfo.defOfssize
    .else
        mov eax,[ecx].dsym.seginfo
        movzx ecx,[eax].seg_info.Ofssize
        mov ModuleInfo.Ofssize,cl
        movzx eax,min_cpu[ecx*2]
        .if ( ModuleInfo.curr_cpu < eax )
            mov eax,16
            shl eax,cl
            .return( asmerr( 2066, eax ) )
        .endif
    .endif
    mov eax,2
    mov cl,ModuleInfo.Ofssize
    shl eax,cl
    mov CurrWordSize,al
    xor eax,eax
    .if ( cl == USE64 )
        inc eax
    .endif
    Set64Bit( eax )
    .return( NOT_ERROR )

SetOfssize endp

; close segment

CloseSeg proc fastcall private uses esi edi sname:string_t

    mov esi,ecx
    mov ecx,CurrSeg
    xor edi,edi
    .if ( ecx == NULL )
        inc edi
    .elseif ( SymCmpFunc( [ecx].asym.name, esi, [ecx].asym.name_size ) != 0 )
        inc edi
    .endif
    .if ( edi )
        .return( asmerr( 1010, esi ) )
    .endif
ifndef __ASMC64__
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

    mov eax,ModuleInfo.flat_grp
    .if ( eax == NULL )

        ; can't fail because <FLAT> is a reserved word

        mov ModuleInfo.flat_grp,CreateGroup( "FLAT" )
        mov cl,ModuleInfo.defOfssize
        mov [eax].asym.Ofssize,cl
    .endif
    or [eax].asym.flags,S_ISDEFINED ; v2.09
    ret

DefineFlatGroup endp

GetSegIdx proc sym:ptr asym

    ; get idx to sym's segment

    mov eax,sym
    .if ( eax )
        mov eax,[eax].dsym.seginfo
        .return( [eax].seg_info.seg_idx )
    .endif
    ret

GetSegIdx endp

GetGroup proc sym:ptr asym

    ; get a symbol's group
    .if ( GetSegm( sym ) != NULL )
        mov eax,[eax].dsym.seginfo
        .return( [eax].seg_info.sgroup )
    .endif
    ret

GetGroup endp

GetSymOfssize proc sym:ptr asym

    ; get sym's offset size (64=2, 32=1, 16=0)

    .if ( GetSegm( sym ) == NULL )
        mov eax,sym
        .if ( [eax].asym.state == SYM_EXTERNAL )
            movzx eax,[eax].asym.segoffsize
            .return
        .endif
        .if ( [eax].asym.state == SYM_STACK || [eax].asym.state == SYM_GRP )
            .return( [eax].asym.Ofssize )
        .endif
        .if ( [eax].asym.state == SYM_SEG  )
            mov eax,[eax].dsym.seginfo
            .return( [eax].seg_info.Ofssize )
        .endif
        ; v2.07: added
        .if ( [eax].asym.mem_type == MT_EMPTY )
            .return( USE16 )
        .endif
    .else
        mov eax,[eax].dsym.seginfo
        .return( [eax].seg_info.Ofssize )
    .endif
    movzx eax,ModuleInfo.Ofssize
    ret

GetSymOfssize endp

SetSymSegOfs proc uses edi sym:ptr asym

    mov edi,sym
    mov [edi].asym.segm,CurrSeg
    mov [edi].asym.offs,GetCurrOffset()
    ret

SetSymSegOfs endp

; get segment type from alignment, combine type or class name

TypeFromClassName proc uses esi edi s:ptr dsym, clname:ptr asym

  local uname[MAX_ID_LEN+1]:char_t

    mov ecx,s
    mov edx,[ecx].dsym.seginfo

    .if ( [edx].seg_info.alignment == MAX_SEGALIGNMENT )
        .return( SEGTYPE_ABS )
    .endif

    ; v2.03: added
    .if ( [edx].seg_info.combine == COMB_STACK )
        .return( SEGTYPE_STACK )
    .endif

    mov edi,clname
    .if ( edi == NULL )
        .return( SEGTYPE_UNDEF )
    .endif

    .if ( _stricmp( [edi].asym.name, GetCodeClass() ) == 0 )
        .return( SEGTYPE_CODE )
    .endif

    movzx esi,[edi].asym.name_size
    lea ecx,[esi+1]
    mov edi,_strupr( memcpy( &uname, [edi].asym.name, ecx ) )

    .switch( esi )
    .case 5
        .if ( memcmp( edi, "CONST", 6 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
        .if ( memcmp( edi, "DBTYP", 6 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
        .if ( memcmp( edi, "DBSYM", 6 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
    .case 4
        .if ( memcmp( &[edi+esi-4], "CODE", 4 ) == 0 )
            .return( SEGTYPE_CODE )
        .endif
        .if ( memcmp( &[edi+esi-4], "DATA", 4 ) == 0 )
            .return( SEGTYPE_DATA )
        .endif
    .case 3
        .if ( memcmp( &[edi+esi-3], "BSS", 3 ) == 0 )
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

FindClass proc private uses esi edi name:string_t, len:int_t

    .for ( edi = ModuleInfo.LnameQueue.head: edi: edi = [edi].qnode.next )
        mov esi,[edi].qnode.sym
        .if ( [esi].asym.state == SYM_CLASS_LNAME )
            .if ( SymCmpFunc( [esi].asym.name, name, len ) == 0 )
                .return( esi )
            .endif
        .endif
    .endf
    .return( NULL )

FindClass endp

; add a class name to the lname queue
; if it doesn't exist yet.

CreateClassLname proc fastcall private uses esi edi ebx name:string_t

    mov ebx,name
    mov esi,strlen( ebx )

    ; max lname is 255 - this is an OMF restriction

    .if ( esi > MAX_LNAME )
        asmerr( 2041 )
        .return( NULL )
    .endif

    .if !FindClass( ebx, esi )

        ; the classes aren't inserted into the symbol table
        ; but they are in a queue

        mov esi,SymAlloc( ebx )
        mov [esi].asym.state,SYM_CLASS_LNAME
        AddLnameItem( esi )
        mov eax,esi
    .endif
    ret

CreateClassLname endp

; set the segment's class. report an error if the class has been set
; already and the new value differs.

SetSegmentClass proc private s:ptr dsym, name:string_t

    .if ( CreateClassLname( name ) == NULL )
        .return( ERROR )
    .endif
    mov ecx,s
    mov ecx,[ecx].dsym.seginfo
    mov [ecx].seg_info.clsym,eax
   .return( NOT_ERROR )

SetSegmentClass endp

; CreateIntSegment(), used for internally defined segments:
; codeview debugging segments, COFF .drectve, COFF .sxdata

CreateIntSegment proc uses edi name:string_t, classname:string_t, alignment:byte, Ofssize:byte, add_global:int_t

    .if ( add_global )
        SymSearch( name )
        .if ( eax == NULL || [eax].asym.state == SYM_UNDEFINED )
            CreateSegment( eax, name, add_global )
        .elseif ( [eax].asym.state != SYM_SEG )
            asmerr( 2005, name )
            .return( NULL )
        .endif
    .else
        CreateSegment( NULL, name, FALSE )
    .endif

    .if ( eax )
        mov edi,eax
        .if ( !( [edi].asym.flags & S_ISDEFINED ) )

            inc ModuleInfo.num_segs
            mov ecx,[edi].dsym.seginfo
            mov [ecx].seg_info.seg_idx,ModuleInfo.num_segs
            AddLnameItem( edi )
            or [edi].asym.flags,S_ISDEFINED ; v2.12: added
        .endif
        mov ecx,[edi].dsym.seginfo
        mov [ecx].seg_info.internal,TRUE ; segment has private buffer
        mov [edi].asym.segm,edi
        mov [ecx].seg_info.alignment,alignment
        mov [ecx].seg_info.Ofssize,Ofssize
        SetSegmentClass( edi, classname )
        .return( edi )
    .endif
    ret

CreateIntSegment endp

; ENDS directive

EndsDir proc uses ebx i:int_t, tokenarray:ptr asm_tok

    mov ebx,tokenarray
    .if ( CurrStruct != NULL )
        .return( EndstructDirective( i, ebx ) )
    .endif
    ; a label must precede ENDS
    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [ebx+ecx].string_ptr ) )
    .endif
    .if ( Parse_Pass != PASS_1 )
        .if ( ModuleInfo.list )
            LstWrite( LSTTYPE_LABEL, 0, NULL )
        .endif
    .endif
    .if ( CloseSeg( [ebx].string_ptr ) == ERROR )
        .return( ERROR )
    .endif
    inc i
    imul ecx,i,asm_tok
    .if ( [ebx+ecx].token != T_FINAL )
        asmerr( 2008, [ebx+ecx].string_ptr )
    .endif
    .return( SetOfssize() )

EndsDir endp

; SEGMENT directive if pass is > 1

SetCurrSeg proc private uses edi ebx i:int_t, tokenarray:ptr asm_tok

    mov ebx,tokenarray
    mov edi,SymSearch( [ebx].string_ptr )
    .if ( edi == NULL || [edi].asym.state != SYM_SEG )
        .return( asmerr( 2006, [ebx].string_ptr ) )
    .endif
    ; v2.04: added
    or [edi].asym.flags,S_ISDEFINED
ifndef __ASMC64__
    .if ( CurrSeg && Options.output_format == OFORMAT_OMF )
        omf_FlushCurrSeg()
        .if ( Options.no_comment_in_code_rec == FALSE )
            omf_OutSelect( FALSE )
        .endif
    .endif
endif
    push_seg( edi )
    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif
    .return( SetOfssize() )

SetCurrSeg endp

UnlinkSeg proc private uses esi edi dir:ptr dsym

    .for ( edi = SymTables[TAB_SEG*symbol_queue].head, esi = NULL: edi: esi = edi, edi = [edi].dsym.next )
        .if ( edi == dir )

            ; if segment is first, set a new head

            .if ( esi == NULL )
                mov SymTables[TAB_SEG*symbol_queue].head,[edi].dsym.next
            .else
                mov [esi].dsym.next,[edi].dsym.next
            .endif

            ; if segment is last, set a new tail

            .if ( [edi].dsym.next == NULL )
                mov SymTables[TAB_SEG*symbol_queue].tail,esi
            .endif
        .endif
    .endf
    ret

UnlinkSeg endp

; SEGMENT directive

SegmentDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

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
   .new dir:ptr dsym
   .new name:string_t
   .new sym:ptr asym
   .new opndx:expr

    mov ebx,tokenarray
    .if ( Parse_Pass != PASS_1 )
        .return( SetCurrSeg( i, ebx ) )
    .endif

    .if ( i != 1 )
        imul ecx,i,asm_tok
        .return( asmerr( 2008, [ebx+ecx].string_ptr ) )
    .endif

    mov name,[ebx].string_ptr

    ; See if the segment is already defined
    mov sym,SymSearch( name )

    .if ( eax == NULL || [eax].asym.state == SYM_UNDEFINED )

        mov newseg,1

        ; segment is not defined (yet)

        mov sym,CreateSegment( sym, name, TRUE )
        or  [eax].asym.flag1,S_LIST ; always list segments
        mov dir,eax

    .elseif ( [eax].asym.state == SYM_SEG ) ; segment already defined?

        mov dir,eax
        mov edi,eax

        .if ( !( [eax].asym.flags & S_ISDEFINED ) )

            ; segment was forward referenced (in a GROUP directive), but not really set up
            ; the segment list is to be sorted.
            ; So unlink the segment and add it at the end.

            UnlinkSeg( edi )
            mov [edi].dsym.next,NULL
            .if ( SymTables[TAB_SEG*symbol_queue].head == NULL )

                mov SymTables[TAB_SEG*symbol_queue].head,edi
                mov SymTables[TAB_SEG*symbol_queue].tail,edi
            .else
                mov ecx,SymTables[TAB_SEG*symbol_queue].tail
                mov [ecx].dsym.next,edi
                mov SymTables[TAB_SEG*symbol_queue].tail,edi
            .endif
        .else
            mov is_old,TRUE
            mov ecx,[edi].dsym.seginfo
            mov oldOfssize,  [ecx].seg_info.Ofssize
            mov oldalign,    [ecx].seg_info.alignment
            mov oldcombine,  [ecx].seg_info.combine
        .endif

    .else

        ; symbol is different kind, error

        .return( asmerr( 2005, name ) )
    .endif

    inc i ; go past SEGMENT

    .for( : i < Token_Count: i++ )

        imul ebx,i,asm_tok
        add ebx,tokenarray

        mov esi,[ebx].string_ptr
        .if ( [ebx].token == T_STRING )

            ; the class name - the only token which is of type STRING
            ; string must be delimited by [double]quotes

            .if ( [ebx].string_delim != '"' && [ebx].string_delim != "'" )
                asmerr( 2008, esi )
                .continue
            .endif

            ; remove the quote delimiters

            inc esi
            mov ecx,[ebx].stringlen
            mov byte ptr [esi+ecx],NULLC

            SetSegmentClass( dir, esi )
            .continue
        .endif

        ; check the rest of segment attributes.

        mov typeidx,FindToken( esi, &SegAttrToken, count_SegAttrToken )
        .if ( typeidx < 0 )
            asmerr( 2015, esi, "attributes" )
            .continue
        .endif
        mov type,&SegAttrValue[eax*typeinfo]

        ; initstate is used to check if any field is already
        ; initialized

        movzx edx,[eax].typeinfo.init
        mov ecx,initstate
        mov eax,edx
        and eax,INIT_EXCL_MASK
        and eax,ecx

        .if ( eax )
            asmerr( 2015, esi, "attributes" )
            .continue
        .endif

        or initstate,edx ; mark it initialized
        mov ecx,dir
        mov edi,[ecx].dsym.seginfo
        mov ecx,type

        .switch ( edx )
        .case INIT_ATTR
            mov [edi].seg_info.readonly,TRUE
            .endc
        .case INIT_ALIGN
            mov al,[ecx].typeinfo.value
            mov [edi].seg_info.alignment,al
            .endc
        .case INIT_ALIGN_PARAM
            .if ( Options.output_format == OFORMAT_OMF )
                asmerr( 3006, [ebx].string_ptr )
                mov i,Token_Count ; stop further parsing of this line
                .endc
            .endif
            inc i
            add ebx,asm_tok
            .if ( [ebx].token != T_OP_BRACKET )
                asmerr( 2065, "(" )
               .endc
            .endif
            inc i
            .endc .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
            imul ebx,i,asm_tok
            add ebx,tokenarray
            .if ( [ebx].token != T_CL_BRACKET )
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
                push edx
                asmerr( 2063, opndx.value )
                pop edx
            .endif
            mov [edi].seg_info.alignment,dl
            .endc
        .case INIT_COMBINE
            mov [edi].seg_info.combine,[ecx].typeinfo.value
            .endc
        .case INIT_COMBINE_AT
            mov [edi].seg_info.combine,[ecx].typeinfo.value
            mov [edi].seg_info.alignment,MAX_SEGALIGNMENT
            inc i
            .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) != ERROR )
                .if ( opndx.kind == EXPR_CONST )
                    mov [edi].seg_info.abs_frame,opndx.value
                    mov [edi].seg_info.abs_offset,0
                .else
                    asmerr( 2026 )
                .endif
            .endif
            .endc
        .case INIT_COMBINE_COMDAT
            .if ( Options.output_format != OFORMAT_COFF && Options.output_format != OFORMAT_OMF )
                asmerr( 3006, [ebx].string_ptr )
                mov i,Token_Count ; stop further parsing of this line
                .endc
            .endif
            inc i
            add ebx,asm_tok
            .if ( [ebx].token != T_OP_BRACKET )
                asmerr( 2065, "(" )
                .endc
            .endif
            inc i
            .endc .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )

            imul ebx,i,asm_tok
            add ebx,tokenarray

            .if ( opndx.kind != EXPR_CONST )
                asmerr( 2026 )
                mov i,Token_Count ; stop further parsing of this line
                .endc
            .endif

            .if ( opndx.value < 1 || opndx.value > 6 )
                asmerr( 2156, "1-6" )
            .else

                ; if value is IMAGE_COMDAT_SELECT_ASSOCIATIVE,
                ; get the associated segment name argument.

                .if ( opndx.value == 5 )
                    ;asym *sym2
                    .if ( [ebx].token != T_COMMA )
                        asmerr( 2008, [ebx].tokpos )
                        mov i,Token_Count ; stop further parsing of this line
                        .endc
                    .endif
                    inc i
                    add ebx,asm_tok
                    .if ( [ebx].token != T_ID )
                        asmerr(2008, [ebx].string_ptr )
                        mov i,Token_Count ; stop further parsing of this line
                        .endc
                    .endif

                    ; associated segment must be COMDAT, but not associative

                    .if SymSearch( [ebx].string_ptr )
                        mov ecx,[eax].dsym.seginfo
                    .endif
                    .if ( eax == NULL || [eax].asym.state != SYM_SEG || \
                        [ecx].seg_info.comdatselection == 0 || \
                        [ecx].seg_info.comdatselection == 5 )
                        asmerr( 2008, [ebx].string_ptr )
                    .else
                        mov [edi].seg_info.comdat_number,[ecx].seg_info.seg_idx
                    .endif
                    inc i
                    add ebx,asm_tok
                .endif
            .endif
            .if ( [ebx].token != T_CL_BRACKET )
                asmerr( 2065, ")" )
                .endc
            .endif
            mov [edi].seg_info.comdatselection,opndx.value
            mov ecx,type
            mov [edi].seg_info.combine,[ecx].typeinfo.value
            .endc
        .case INIT_OFSSIZE
        .case INIT_OFSSIZE_FLAT
            .if ( [ecx].typeinfo.init == INIT_OFSSIZE_FLAT )
                DefineFlatGroup()

                ; v2.09: make sure ofssize is at least USE32 for FLAT

                mov al,USE32
                .if ( ModuleInfo.defOfssize > USE16 )
                    mov al,ModuleInfo.defOfssize
                .endif
                mov [edi].seg_info.Ofssize,al

                ; put the segment into the FLAT group.
                ; this is not quite Masm-compatible, because trying to put
                ; the segment into another group will cause an error.

                mov [edi].seg_info.sgroup,ModuleInfo.flat_grp
            .else
                mov ecx,type
                mov [edi].seg_info.Ofssize,[ecx].typeinfo.value
            .endif
            .endc
        .case INIT_CHAR_INFO
            mov [edi].seg_info.info,TRUE ; fixme: check that this flag isn't changed
            .endc
        .case INIT_CHAR
            ; characteristics are restricted to COFF/ELF/BIN-PE
            .if ( Options.output_format == OFORMAT_OMF || ( Options.output_format == OFORMAT_BIN && \
                ( ModuleInfo.sub_format != SFORMAT_PE && ModuleInfo.sub_format != SFORMAT_64BIT ) ) )
                asmerr( 3006, [ebx].string_ptr )
            .else
                or newcharacteristics,[ecx].typeinfo.value
            .endif
            .endc
        .case INIT_ALIAS
            ; alias() is restricted to COFF/ELF/BIN-PE
            .if ( Options.output_format == OFORMAT_OMF || ( Options.output_format == OFORMAT_BIN && \
                ( ModuleInfo.sub_format != SFORMAT_PE && ModuleInfo.sub_format != SFORMAT_64BIT ) ) )
                asmerr( 3006, [ebx].string_ptr )
                mov i,Token_Count ; stop further parsing of this line
                .endc
            .endif
            inc i
            add ebx,asm_tok
            .if ( [ebx].token != T_OP_BRACKET )
                asmerr( 2065, "(" )
                .endc
            .endif
            inc i
            add ebx,asm_tok
            .if ( [ebx].token != T_STRING || ( [ebx].string_delim != '"' && [ebx].string_delim != "'" ) )
                asmerr(2008, token )
                mov i,Token_Count ; stop further parsing of this line
                .endc
            .endif
            mov esi,ebx
            inc i
            add ebx,asm_tok
            .if ( [ebx].token != T_CL_BRACKET )
                asmerr( 2065, ")" )
                .endc
            .endif
            mov ebx,esi

            ; v2.10: if segment already exists, check that old and new aliasname are equal

            .if ( is_old )

                .if ( [edi].seg_info.aliasname )

                    mov esi,strlen( [edi].seg_info.aliasname )
                    mov ecx,[ebx].string_ptr
                    inc ecx
                    memcmp( [edi].seg_info.aliasname, ecx, [ebx].stringlen )
                .endif

                .if ( [edi].seg_info.aliasname == NULL || ( [ebx].stringlen != esi ) || eax )

                    mov ecx,dir
                    asmerr( 2015, [ecx].asym.name, "alias" )
                    .endc
                .endif

            .else

                ; v2.10: " + 1" was missing in next line

                mov ecx,[ebx].stringlen
                inc ecx
                mov [edi].seg_info.aliasname,LclAlloc( ecx )
                mov ecx,[ebx].string_ptr
                inc ecx
                mov esi,[ebx].stringlen
                memcpy( [edi].seg_info.aliasname, ecx, esi )
                mov byte ptr [eax+esi],NULLC
            .endif
            .endc
        .endsw
    .endf

    ; make a guess about the segment's type

    mov ecx,dir
    mov edi,[ecx].dsym.seginfo

    .if ( [edi].seg_info.segtype != SEGTYPE_CODE )

        TypeFromClassName( dir, [edi].seg_info.clsym )
        .if ( eax != SEGTYPE_UNDEF )
            mov [edi].seg_info.segtype,eax
        .endif
    .endif

    .if ( is_old )

        xor esi,esi

        ; Check if new definition is different from previous one

        .if ( oldalign != [edi].seg_info.alignment )
            lea esi,@CStr("alignment")
        .elseif ( oldcombine != [edi].seg_info.combine )
            lea esi,@CStr("combine")
        .elseif ( oldOfssize != [edi].seg_info.Ofssize )
            lea esi,@CStr("segment word size")
        .elseif ( newcharacteristics && ( newcharacteristics != [edi].seg_info.characteristics ) )
            lea esi,@CStr("characteristics")
        .endif

        .if ( esi )
            mov ecx,dir
            asmerr( 2015, [ecx].asym.name, esi )
        .endif

    .else

        ; A new definition
        mov ecx,sym
        or  [ecx].asym.flags,S_ISDEFINED
        mov [ecx].asym.segm,ecx
        mov [ecx].asym.offs,0 ; remains 0 ( =segment's local start offset )

        ; no segment index for COMDAT segments in OMF!

        .if ( [edi].seg_info.comdatselection && Options.output_format == OFORMAT_OMF )

        .else
            inc ModuleInfo.num_segs
            mov [edi].seg_info.seg_idx,ModuleInfo.num_segs
            AddLnameItem( ecx )
        .endif

    .endif
    .if ( newcharacteristics )
        mov [edi].seg_info.characteristics,newcharacteristics
    .endif

    push_seg( dir ) ; set CurrSeg

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif

    mov esi,SetOfssize()
    .if ( Options.debug_symbols == 4 && newseg )
        .if ( [edi].seg_info.segtype == SEGTYPE_CODE && CV8Label == NULL )
            mov CV8Label,CreateLabel( "$$000000", 0, 0, 0 )
        .endif
    .endif
    .return( esi )

SegmentDir endp

; sort segments ( a simple bubble sort )
; type,0: sort by fileoffset (.DOSSEG )
; type,1: sort by name ( .ALPHA )
; type,2: sort by segment type+name ( PE format ). member lname_idx is misused here for "type"

    assume ebx:nothing

SortSegments proc uses esi edi ebx type:int_t

    .new changed:int_t = TRUE
    .new swap:int_t
    .new curr:ptr dsym
    .new index:int_t = 1

    .while ( changed == TRUE )

        xor esi,esi
        mov changed,FALSE

        .for ( edi = SymTables[TAB_SEG*symbol_queue].head: edi && [edi].dsym.next : esi = edi, edi = [edi].dsym.next )

            mov swap,FALSE
            mov ebx,[edi].dsym.seginfo

            .switch (type )
            .case 0
                mov ecx,[edi].dsym.next
                mov ecx,[ecx].dsym.seginfo
                .if ( [ebx].seg_info.fileoffset > [ecx].seg_info.fileoffset )
                    mov swap,TRUE
                .endif
                .endc
            .case 1
                mov ecx,[edi].dsym.next
                .ifs ( strcmp( [edi].asym.name, [ecx].asym.name ) > 0 )
                    mov swap,TRUE
                .endif
                .endc
            .case 2
                mov edx,[edi].dsym.next
                mov ecx,[edx].dsym.seginfo
                .if ( [ebx].seg_info.lname_idx > [ecx].seg_info.lname_idx )
                    mov swap,TRUE
                .elseif ( [ebx].seg_info.lname_idx == [ecx].seg_info.lname_idx )
                    .ifs ( _stricmp( [edi].asym.name, [edx].asym.name ) > 0 )
                        mov swap,TRUE
                    .endif
                .endif
                .endc
            .endsw
            .if ( swap )
                mov edx,[edi].dsym.next
                mov changed,TRUE
                .if ( esi == NULL )
                    mov SymTables[TAB_SEG*symbol_queue].head,edx
                .else
                    mov [esi].dsym.next,edx
                .endif
                mov [edi].dsym.next,[edx].dsym.next
                mov [edx].dsym.next,edi
            .endif
        .endf
    .endw
    ret

SortSegments endp

; END directive has been found.

SegmentModuleExit proc uses edi

    .if ( ModuleInfo._model != MODEL_NONE )
        ModelSimSegmExit()
    .endif

    ; if there's still an open segment, it's an error
    mov edi,CurrSeg
    .if ( edi )
        asmerr( 1010, [edi].asym.name )

        ; but close the still open segments anyway

        .while( edi )
            .break .if ( CloseSeg( [edi].asym.name ) != NOT_ERROR )
            mov edi,CurrSeg
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

SegmentInit proc uses esi edi ebx pass:int_t

    .new curr:ptr dsym
    .new i:uint_32
    .new p:string_t

    mov CurrSeg,NULL
    mov stkindex,0

    .if ( pass == PASS_1 )
        mov grpdefidx,0
        mov buffer_size,0
        mov CV8Label,NULL
    .endif

    ; alloc a buffer for the contents

    .if ( ModuleInfo.pCodeBuff == NULL && Options.output_format != OFORMAT_OMF )
        .for ( edi = SymTables[TAB_SEG*symbol_queue].head,
                buffer_size = 0: edi: edi = [edi].dsym.next )

            mov ecx,[edi].dsym.seginfo
            .continue .if ( [ecx].seg_info.internal )

            .if ( [ecx].seg_info.bytes_written )

                mov eax,[edi].asym.max_offset
                sub eax,[ecx].seg_info.start_loc

                ; the segment can grow in step 2-n due to forward references.
                ; for a quick solution just add 25% to the size if segment
                ; is a code segment. (v2.02: previously if was added only if
                ; code segment contained labels, but this isn't sufficient.)

                .if ( [ecx].seg_info.segtype == SEGTYPE_CODE )

                    mov edx,eax
                    shr eax,2
                    add eax,edx
                .endif
                add buffer_size,eax
            .endif
        .endf
        .if ( buffer_size )
            mov ModuleInfo.pCodeBuff,LclAlloc( buffer_size )
        .endif
    .endif

    ; Reset length of all segments to zero.
    ; set start of segment buffers.

    .for ( edi = SymTables[TAB_SEG*symbol_queue].head,
           esi = ModuleInfo.pCodeBuff: edi: edi = [edi].dsym.next )

        mov ecx,[edi].dsym.seginfo
        mov [ecx].seg_info.current_loc,0
        .continue .if ( [ecx].seg_info.internal )

        .if ( [ecx].seg_info.bytes_written )
            .if ( Options.output_format == OFORMAT_OMF )
                mov [ecx].seg_info.CodeBuffer,&codebuf
            .else
                mov [ecx].seg_info.CodeBuffer,esi
                mov eax,[edi].asym.max_offset
                sub eax,[ecx].seg_info.start_loc
                add esi,eax
            .endif
        .endif
        .if ( [ecx].seg_info.combine != COMB_STACK )
            mov [edi].asym.max_offset,0
        .endif
        .if ( Options.output_format == OFORMAT_OMF )  ;; v2.03: do this selectively
            mov [ecx].seg_info.start_loc,0
            mov [ecx].seg_info.data_in_code,FALSE
        .endif
        mov [ecx].seg_info.bytes_written,0
        mov [ecx].seg_info.head,NULL
        mov [ecx].seg_info.tail,NULL
    .endf

    mov ModuleInfo.Ofssize,USE16

    .if ( pass != PASS_1 && UseSavedState == TRUE )
        mov CurrSeg,saved_CurrSeg
        mov stkindex,saved_stkindex
        .if ( stkindex )
            imul ecx,stkindex,sizeof(dsym_t)
            memcpy( &SegStack, saved_SegStack, ecx )
        .endif
        UpdateCurrSegVars()
    .endif
    ret

SegmentInit endp

SegmentSaveState proc

    mov saved_CurrSeg,CurrSeg
    mov saved_stkindex,stkindex
    .if ( stkindex )
        imul ecx,stkindex,sizeof(dsym_t)
        mov saved_SegStack,LclAlloc( ecx )
        imul ecx,stkindex,sizeof(dsym_t)
        memcpy( saved_SegStack, &SegStack, ecx )
    .endif
    ret
SegmentSaveState endp

    end
