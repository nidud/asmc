; SAFESEH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  processes directive .SAFESEH
;

include asmc.inc
include memalloc.inc
include parser.inc

;; .SAFESEH works for coff format only.
;; syntax is: .SAFESEH handler
;; <handler> must be a PROC or PROTO

    .code

    assume ebx:ptr asm_tok
    assume edi:ptr qnode

SafeSEHDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

    imul ebx,i,asm_tok
    add ebx,tokenarray

    .if ( Options.output_format != OFORMAT_COFF )
        .if ( Parse_Pass == PASS_1)
            asmerr( 8015, "coff" )
        .endif
        .return( NOT_ERROR )
    .endif
    .if ( Options.safeseh == FALSE )
        .if ( Parse_Pass == PASS_1)
            asmerr( 8015, "safeseh" )
        .endif
        .return( NOT_ERROR )
    .endif
    inc i
    add ebx,asm_tok
    .if ( [ebx].token != T_ID )
        .return( asmerr(2008, [ebx].string_ptr ) )
    .endif
    mov esi,SymSearch( [ebx].string_ptr )

    ;; make sure the argument is a true PROC
    .if ( esi == NULL || [esi].asym.state == SYM_UNDEFINED )
        .if ( Parse_Pass != PASS_1 )
            .return( asmerr( 2006, [ebx].string_ptr ) )
        .endif
    .elseif ( !( [esi].asym.flag1 & S_ISPROC ) )
        .return( asmerr( 3017, [ebx].string_ptr ) )
    .endif

    .if ( Parse_Pass == PASS_1 )
        .if ( esi )
            .for ( edi = ModuleInfo.SafeSEHQueue.head: edi: edi = [edi].next )
                .break .if ( [edi].elmt == esi )
            .endf
        .else
            mov esi,SymCreate( [ebx].string_ptr )
            mov edi,NULL
        .endif
        .if ( edi == NULL )
            or [esi].asym.flags,S_USED ;; make sure an external reference will become strong
            QAddItem( &ModuleInfo.SafeSEHQueue, esi )
        .endif
    .endif
    inc i
    add ebx,asm_tok
    .if ( [ebx].token != T_FINAL )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif
    .return( NOT_ERROR )
SafeSEHDirective endp

    end
