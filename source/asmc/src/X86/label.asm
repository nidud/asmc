; LABEL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: Label directive, (anonymous) code labels
;

include asmc.inc
include parser.inc
include fixup.inc
include segment.inc
include proc.inc
include assume.inc
include types.inc
include label.inc
include listing.inc

;; LABELARRAY: syntax extension to LABEL directive:
;;  <label> LABEL <qualified type>[: index]


define LABELARRAY 1

if LABELARRAY
include expreval.inc
endif

.code

LabelInit proc

    mov ModuleInfo.anonymous_label,0
    ret

LabelInit endp

GetAnonymousLabel proc buffer:string_t, value:int_t

    mov eax,ModuleInfo.anonymous_label
    add eax,value
    sprintf( buffer, "L&_%04u", eax )
    .return( buffer )

GetAnonymousLabel endp

;; define a (code) label.
;; - name: name of the label; ensured to be a valid identifier
;; - mem_type: label's memory type
;; - ti: qualified type pointer, used if memtype is MT_TYPE or MT_PROC
;; - bLocal: if TRUE, code label is to be defined locally; it's ensured
;;   that CurrProc is != NULL and ModuleInfo.scoped == TRUE then.

CreateLabel proc uses esi edi ebx name:string_t, mem_type:byte, ti:ptr qualified_type, bLocal:int_t

  local adr:uint_t
  local buffer[20]:char_t

    .if ( CurrSeg == NULL )
        asmerr( 2034 )
        .return( NULL )
    .endif

    ;; v2.06: don't allow a code label (NEAR, FAR, PROC) if CS is
    ;; assumed ERROR. This was previously checked for labels with
    ;; trailing colon only [in ParseLine()].

    mov al,mem_type
    and al,MT_SPECIAL_MASK
    .if ( al == MT_ADDRESS )
        .if ( SegAssumeTable[ASSUME_CS*8].error ) ;; CS assumed to ERROR?
            asmerr( 2108 )
            .return( NULL )
        .endif
    .endif
    mov esi,name
    mov eax,[esi]
    and eax,0x00FFFFFF
    .if ( eax == '@@' )

        lea esi,buffer
        inc ModuleInfo.anonymous_label
        sprintf( esi, "L&_%04u", ModuleInfo.anonymous_label )
    .endif

    .if ( bLocal )
        SymLookupLocal( esi )
    .else
        SymLookup( esi )
    .endif
    mov edi,eax

    .if( Parse_Pass == PASS_1 )
        .if( [edi].asym.state == SYM_EXTERNAL && [edi].asym.sflags & S_WEAK )
            ;; don't accept EXTERNDEF for a local label!
            .if ( [edi].asym.flag1 & S_ISPROC || ( bLocal && CurrProc ) )
                asmerr( 2005, name )
                .return( NULL )
            .endif
            ;; ensure that type of symbol is compatible!
            .if ( [edi].asym.mem_type != MT_EMPTY && [edi].asym.mem_type != mem_type )
                asmerr( 2004, esi )
            .endif
            sym_ext2int( edi )
        .elseif( [edi].asym.state == SYM_UNDEFINED )
            sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], edi )
            mov [edi].asym.state,SYM_INTERNAL
        .else
            asmerr(2005, esi )
            .return( NULL )
        .endif
        ;; add the label to the linked list attached to curr segment
        ;; this allows to reduce the number of passes (see fixup.c)

        mov ecx,CurrSeg
        mov ecx,[ecx].dsym.seginfo

        mov [edi].dsym.next,[ecx].seg_info.label_list
        mov [ecx].seg_info.label_list,edi

        ;; a possible language type set by EXTERNDEF must be kept!
        .if ( [edi].asym.langtype == LANG_NONE )
            mov [edi].asym.langtype,ModuleInfo.langtype
        .endif

        assume ebx:ptr qualified_type
        mov ebx,ti
        ;; v2.05: added to accept type prototypes
        .if ( mem_type == MT_PROC )
            .if ( !( [edi].asym.flag1 & S_ISPROC ) )
                CreateProc( edi, NULL, SYM_INTERNAL )
                CopyPrototype( edi, [ebx].symtype )
            .endif
            mov ecx,[ebx].symtype
            mov mem_type,[ecx].asym.mem_type
            mov [ebx].symtype,NULL
        .endif

        mov [edi].asym.mem_type,mem_type
        .if ( ebx )
            .if ( mem_type == MT_TYPE )
                mov [edi].asym.type,[ebx].symtype
            .else
                mov [edi].asym.Ofssize,[ebx].Ofssize
                mov [edi].asym.is_ptr,[ebx].is_ptr
                .if [ebx].is_far
                    or [edi].asym.sflags,S_ISFAR
                .endif
                mov [edi].asym.target_type,[ebx].symtype
                mov [edi].asym.ptr_memtype,[ebx].ptr_memtype
            .endif
        .endif
    .else
        ;; save old offset
        mov adr,[edi].asym.offs
    .endif

    or [edi].asym.flags,S_ISDEFINED
    ;; v2.05: the label may be "data" - due to the way struct initialization
    ;; is handled. Then fields first_size and first_length must not be
    ;; touched!

    .if ( !( [edi].asym.flag1 & S_ISDATA ) )
        mov [edi].asym.asmpass,Parse_Pass
    .endif
    SetSymSegOfs( edi )

    .if ( Parse_Pass != PASS_1 && [edi].asym.offs != adr )
        mov ModuleInfo.PhaseError,TRUE
    .endif
    BackPatch( edi )
    .return( edi )

CreateLabel endp

;; LABEL directive.
;; syntax: <label_name> LABEL <qualified type>

LabelDirective proc uses ebx i:int_t, tokenarray:ptr asm_tok

  local ti:qualified_type
if LABELARRAY
  local length:uint_32
endif

    imul ebx,i,asm_tok
    add ebx,tokenarray
    assume ebx:ptr asm_tok
    .if ( i != 1 ) ;; LABEL must be preceded by an ID
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif

    inc i
    mov ti.size,0
    mov ti.is_ptr,0
    mov ti.is_far,FALSE
    mov ti.mem_type,MT_EMPTY
    mov ti.ptr_memtype,MT_EMPTY
    mov ti.symtype,NULL
    mov ti.Ofssize,ModuleInfo.Ofssize
    .return .if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )

    imul ebx,i,asm_tok
    add ebx,tokenarray

if LABELARRAY
    mov length,-1
endif
    ;; v2.10: first if()-block is to handle all address types ( MT_NEAR, MT_FAR and MT_PROC )
    mov al,ti.mem_type
    and al,MT_SPECIAL_MASK
    .if (  al == MT_ADDRESS )
        ;; dont allow near16/far16/near32/far32 if size won't match
        .if ( ti.Ofssize != USE_EMPTY && ModuleInfo.Ofssize != ti.Ofssize )
            .return( asmerr( 2098 ) )
        .endif
if LABELARRAY
    .elseif ( [ebx].token == T_COLON && [ebx+16].token != T_FINAL && \
            ModuleInfo.strict_masm_compat == FALSE )

       .new opnd:expr
        inc i

       .return .if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )

        imul ebx,i,asm_tok
        add ebx,tokenarray

        .if ( opnd.kind != EXPR_CONST )
            mov ecx,opnd.sym
            .if ( ecx && [ecx].asym.state == SYM_UNDEFINED )
                mov opnd.value,1
            .else
                .return( asmerr( 2026 ) )
            .endif
        .endif
        mov length,opnd.value
endif
    .endif

    .if ( [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].tokpos ) ) ;; v2.10: display tokpos
    .endif

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif

    ;; v2.08: if label is a DATA label, set total_size and total_length
    mov ebx,tokenarray
    .if ( CreateLabel( [ebx].string_ptr, ti.mem_type, &ti, FALSE ) )

        ;; sym->isdata must be 0, else the LABEL directive was generated within data_item()
        ;; and fields total_size & total_length must not be modified then!
        ;; v2.09: data_item() no longer creates LABEL directives.

        mov ecx,eax
        mov al,[ecx].asym.mem_type
        and al,MT_SPECIAL_MASK
        .if ( !( [ecx].asym.flag1 & S_ISDATA ) && al != MT_ADDRESS )
if LABELARRAY
            .if ( length != -1 )
                mov eax,ti.size
                mul length
                mov [ecx].asym.total_size,eax
                mov [ecx].asym.total_length,length
                or  [ecx].asym.flag1,S_ISARRAY
            .else
                mov [ecx].asym.total_size,ti.size
                mov [ecx].asym.total_length,1
            .endif
else
            mov [ecx].asym.total_size,ti.size
            mov [ecx].asym.total_length,1
endif
        .endif
        .return( NOT_ERROR )
    .endif
    .return( ERROR )
LabelDirective endp

    end

