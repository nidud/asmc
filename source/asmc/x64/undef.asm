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

UndefDirective proc uses rsi rbx i:int_t, tokenarray:ptr asm_tok

    mov  esi,i
    inc  esi ;; skip directive

    imul ebx,esi,asm_tok
    add  rbx,tokenarray

    .repeat

        .if ( [rbx].token != T_ID )

            .return( asmerr(2008, [rbx].string_ptr ) )
        .endif

        SymSearch( [rbx].string_ptr )

        .if eax

            mov [rax].asym.state,SYM_UNDEFINED
        .endif

        inc esi
        add rbx,asm_tok

        .if ( esi < Token_Count )

            .if ( [rbx].token != T_COMMA || [rbx+asm_tok].token == T_FINAL )

                .return( asmerr(2008, [rbx].tokpos ) )
            .endif

            inc esi
            add rbx,asm_tok

        .endif
    .until ( esi >= Token_Count )

    .return( NOT_ERROR )

UndefDirective endp

    end

