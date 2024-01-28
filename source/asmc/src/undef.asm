; UNDEF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; UNDEF directive.
;
; syntax: UNDEF symbol [, symbol, ... ]
;

include asmc.inc
include parser.inc

    .code

    assume rbx:ptr asm_tok

UndefDirective proc __ccall uses rsi rbx i:int_t, tokenarray:ptr asm_tok

    ldr  esi,i
    ldr  rbx,tokenarray

    inc  esi ;; skip directive
    imul eax,esi,asm_tok
    add  rbx,rax

    .repeat

        .if ( [rbx].token != T_ID )

            .return( asmerr( 2008, [rbx].string_ptr ) )
        .endif

        SymSearch( [rbx].string_ptr )

        .if ( rax )

            mov [rax].asym.state,SYM_UNDEFINED
        .endif

        inc esi
        add rbx,asm_tok

        .if ( esi < TokenCount )

            .if ( [rbx].token != T_COMMA || [rbx+asm_tok].token == T_FINAL )

                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif

            inc esi
            add rbx,asm_tok

        .endif
    .until ( esi >= TokenCount )
    .return( NOT_ERROR )

UndefDirective endp

    end

