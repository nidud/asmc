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

    assume ebx:ptr asm_tok

UndefDirective proc uses esi ebx i:int_t, tokenarray:ptr asm_tok

    mov  esi,i
    inc  esi ;; skip directive

    imul ebx,esi,asm_tok
    add  ebx,tokenarray

    .repeat

        .if ( [ebx].token != T_ID )

            .return( asmerr(2008, [ebx].string_ptr ) )
        .endif

        SymSearch( [ebx].string_ptr )

        .if eax

            mov [eax].asym.state,SYM_UNDEFINED
        .endif

        inc esi
        add ebx,asm_tok

        .if ( esi < Token_Count )

            .if ( [ebx].token != T_COMMA || [ebx+16].token == T_FINAL )

                .return( asmerr(2008, [ebx].tokpos ) )
            .endif

            inc esi
            add ebx,asm_tok

        .endif
    .until ( esi >= Token_Count )

    .return( NOT_ERROR )

UndefDirective endp

    end

