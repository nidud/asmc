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

; LABELARRAY: syntax extension to LABEL directive:
;  <label> LABEL <qualified type>[: index]


define LABELARRAY 1

if LABELARRAY
include expreval.inc
endif

.code

LabelInit proc __ccall

    mov MODULE.anonymous_label,0
    ret

LabelInit endp


GetAnonymousLabel proc __ccall buffer:string_t, value:int_t

    mov eax,MODULE.anonymous_label
    add eax,value
    tsprintf( buffer, "L&_%04u", eax )
   .return( buffer )

GetAnonymousLabel endp


; define a (code) label.
; - name: name of the label; ensured to be a valid identifier
; - mem_type: label's memory type
; - ti: qualified type pointer, used if memtype is MT_TYPE or MT_PROC
; - bLocal: if TRUE, code label is to be defined locally; it's ensured
;   that CurrProc is != NULL and ModuleInfo.scoped == TRUE then.

CreateLabel proc __ccall uses rsi rdi rbx name:string_t, mem_type:byte, ti:ptr qualified_type, bLocal:int_t

  local adr:uint_t
  local buffer[20]:char_t

    .if ( CurrSeg == NULL )

        asmerr( 2034 )
       .return( NULL )
    .endif

    ; v2.06: don't allow a code label (NEAR, FAR, PROC) if CS is
    ; assumed ERROR. This was previously checked for labels with
    ; trailing colon only [in ParseLine()].

    mov al,mem_type
    and al,MT_SPECIAL_MASK
    .if ( al == MT_ADDRESS )
        .if ( SegAssumeTable[ASSUME_CS*assume_info].error ) ; CS assumed to ERROR?

            asmerr( 2108 )
           .return( NULL )
        .endif
    .endif

    mov rsi,name
    mov eax,[rsi]
    and eax,0x00FFFFFF

    .if ( eax == '@@' )

        lea rsi,buffer
        inc MODULE.anonymous_label
        tsprintf( rsi, "L&_%04u", MODULE.anonymous_label )
    .endif

    .if ( bLocal )
        SymLookupLocal( rsi )
    .else
        SymLookup( rsi )
    .endif
    mov rdi,rax

    .if ( Parse_Pass == PASS_1 )

        .if( [rdi].asym.state == SYM_EXTERNAL && [rdi].asym.weak )

            ; don't accept EXTERNDEF for a local label!

            .if ( [rdi].asym.isproc || ( bLocal && CurrProc ) )

                asmerr( 2005, name )
               .return( NULL )
            .endif

            ; ensure that type of symbol is compatible!

            .if ( [rdi].asym.mem_type != MT_EMPTY && [rdi].asym.mem_type != mem_type )
                asmerr( 2004, rsi )
            .endif

            sym_ext2int( rdi )

        .elseif ( [rdi].asym.state == SYM_UNDEFINED )

            sym_remove_table( &SymTables[TAB_UNDEF], rdi )
            mov [rdi].asym.state,SYM_INTERNAL

        .else

            asmerr(2005, rsi )
           .return( NULL )
        .endif

        ; add the label to the linked list attached to curr segment
        ; this allows to reduce the number of passes (see fixup.c)

        mov rcx,CurrSeg
        mov rcx,[rcx].asym.seginfo

        mov [rdi].asym.next,[rcx].seg_info.label_list
        mov [rcx].seg_info.label_list,rdi

        ; a possible language type set by EXTERNDEF must be kept!

        .if ( [rdi].asym.langtype == LANG_NONE )
            mov [rdi].asym.langtype,MODULE.langtype
        .endif

        assume rbx:ptr qualified_type
        mov rbx,ti

        ; v2.05: added to accept type prototypes

        .if ( mem_type == MT_PROC )

            .if ( !( [rdi].asym.isproc ) )

                CreateProc( rdi, NULL, SYM_INTERNAL )
                CopyPrototype( rdi, [rbx].symtype )
            .endif

            mov rcx,[rbx].symtype
            mov mem_type,[rcx].asym.mem_type
            mov [rbx].symtype,NULL
        .endif

        mov [rdi].asym.mem_type,mem_type

        .if ( rbx )

            .if ( mem_type == MT_TYPE )

                mov [rdi].asym.type,[rbx].symtype

            .else

                mov [rdi].asym.Ofssize,[rbx].Ofssize
                mov [rdi].asym.is_ptr,[rbx].is_ptr
                mov [rdi].asym.is_far,[rbx].is_far
                mov [rdi].asym.target_type,[rbx].symtype
                mov [rdi].asym.ptr_memtype,[rbx].ptr_memtype
            .endif
        .endif
    .else

        ; save old offset

        mov adr,[rdi].asym.offs
    .endif

    mov [rdi].asym.isdefined,1

    ; v2.05: the label may be "data" - due to the way struct initialization
    ; is handled. Then fields first_size and first_length must not be
    ; touched!

    .if ( !( [rdi].asym.isdata ) )
        mov [rdi].asym.asmpass,Parse_Pass
    .endif
    SetSymSegOfs( rdi )

    .if ( Parse_Pass != PASS_1 && [rdi].asym.offs != adr )
        mov MODULE.PhaseError,TRUE
    .endif

    BackPatch( rdi )
   .return( rdi )

CreateLabel endp


; LABEL directive.
; syntax: <label_name> LABEL <qualified type>

LabelDirective proc __ccall uses rbx i:int_t, tokenarray:token_t

  local ti:qualified_type
if LABELARRAY
  local length:uint_32
endif

    imul ebx,i,asm_tok
    add rbx,tokenarray
    assume rbx:token_t

    .if ( i != 1 ) ; LABEL must be preceded by an ID
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif

    inc i
    mov ti.size,0
    mov ti.is_ptr,0
    mov ti.is_far,FALSE
    mov ti.mem_type,MT_EMPTY
    mov ti.ptr_memtype,MT_EMPTY
    mov ti.symtype,NULL
    mov ti.Ofssize,MODULE.Ofssize

    .ifd ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
        .return
    .endif

    imul ebx,i,asm_tok
    add rbx,tokenarray

if LABELARRAY
    mov length,-1
endif

    ; v2.10: first if()-block is to handle all address types ( MT_NEAR, MT_FAR and MT_PROC )

    mov al,ti.mem_type
    and al,MT_SPECIAL_MASK

    .if (  al == MT_ADDRESS )

        ; dont allow near16/far16/near32/far32 if size won't match

        .if ( ti.Ofssize != USE_EMPTY && MODULE.Ofssize != ti.Ofssize )
            .return( asmerr( 2098 ) )
        .endif

if LABELARRAY

    .elseif ( [rbx].token == T_COLON && [rbx+asm_tok].token != T_FINAL &&
            Options.strict_masm_compat == FALSE )

       .new opnd:expr
        inc i

        .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR )
            .return
        .endif

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( opnd.kind != EXPR_CONST )

            mov rcx,opnd.sym
            .if ( rcx && [rcx].asym.state == SYM_UNDEFINED )
                mov opnd.value,1
            .else
                .return( asmerr( 2026 ) )
            .endif
        .endif

        mov length,opnd.value
endif

    .endif

    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].tokpos ) ) ; v2.10: display tokpos
    .endif

    .if ( MODULE.list )
        LstWrite( LSTTYPE_LABEL, 0, NULL )
    .endif

    ; v2.08: if label is a DATA label, set total_size and total_length

    mov rbx,tokenarray
    .if ( CreateLabel( [rbx].string_ptr, ti.mem_type, &ti, FALSE ) )

        ; sym->isdata must be 0, else the LABEL directive was generated within data_item()
        ; and fields total_size & total_length must not be modified then!
        ; v2.09: data_item() no longer creates LABEL directives.

        mov rcx,rax
        mov al,[rcx].asym.mem_type
        and al,MT_SPECIAL_MASK

        .if ( !( [rcx].asym.isdata ) && al != MT_ADDRESS )

if LABELARRAY
            .if ( length != -1 )

                mov eax,ti.size
                mul length
                mov [rcx].asym.total_size,eax
                mov [rcx].asym.total_length,length
                mov [rcx].asym.isarray,1
            .else
                mov [rcx].asym.total_size,ti.size
                mov [rcx].asym.total_length,1
            .endif
else
            mov [rcx].asym.total_size,ti.size
            mov [rcx].asym.total_length,1
endif
        .endif
        .return( NOT_ERROR )
    .endif
    .return( ERROR )

LabelDirective endp

    end

