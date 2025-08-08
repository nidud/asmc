; SAFESEH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  processes directive .SAFESEH
;

include asmc.inc

; .SAFESEH works for coff format only.
; syntax is: .SAFESEH handler
; <handler> must be a PROC or PROTO

    .code

    assume rbx:token_t
    assume rdi:ptr qnode

SafeSEHDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

    ldr ecx,i
    ldr rdx,tokenarray

    imul ebx,ecx,asm_tok
    add rbx,rdx

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
    add rbx,asm_tok
    .if ( [rbx].token != T_ID )
        .return( asmerr(2008, [rbx].string_ptr ) )
    .endif
    mov rsi,SymSearch( [rbx].string_ptr )

    ;; make sure the argument is a true PROC
    .if ( rsi == NULL || [rsi].asym.state == SYM_UNDEFINED )
        .if ( Parse_Pass != PASS_1 )
            .return( asmerr( 2006, [rbx].string_ptr ) )
        .endif
    .elseif ( !( [rsi].asym.isproc ) )
        .return( asmerr( 3017, [rbx].string_ptr ) )
    .endif

    .if ( Parse_Pass == PASS_1 )
        .if ( rsi )
            .for ( rdi = MODULE.SafeSEHQueue.head: rdi: rdi = [rdi].next )
                .break .if ( [rdi].elmt == rsi )
            .endf
        .else
            mov rsi,SymCreate( [rbx].string_ptr )
            mov edi,NULL
        .endif
        .if ( rdi == NULL )
            mov [rsi].asym.used,1 ;; make sure an external reference will become strong
            QAddItem( &MODULE.SafeSEHQueue, rsi )
        .endif
    .endif
    inc i
    add rbx,asm_tok
    .if ( [rbx].token != T_FINAL )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif
    .return( NOT_ERROR )

SafeSEHDirective endp

    end
