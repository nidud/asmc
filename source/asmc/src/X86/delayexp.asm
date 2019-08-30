include asmc.inc
include fastpass.inc

    .code

    assume ecx:tok_t

DelayExpand proc fastcall tokenarray:tok_t

    xor eax,eax
    .return .if !( [ecx].hll_flags & T_HLL_DELAY )
    .return .if ModuleInfo.strict_masm_compat
    .return .if Parse_Pass != PASS_1
    .return .if eax != NoLineStore

    .repeat

        .repeat
            .ifs eax >= ModuleInfo.token_count
                or [ecx].hll_flags,T_HLL_DELAYED
                .return 1
            .endif
            lea edx,[eax*8]
            test [ecx+edx*2].hll_flags,T_HLL_MACRO
            lea eax,[eax+1]
            .continue(0) .ifz
        .until [ecx+edx*2].token == T_OP_BRACKET

        mov edx,1   ; one open bracket found
        .while 1

            .ifs eax >= ModuleInfo.token_count
                or [ecx].hll_flags,T_HLL_DELAYED
                .return 1
            .endif

            shl eax,4
            .switch [ecx+eax].token
              .case T_OP_BRACKET
                add edx,1
                .endc
              .case T_CL_BRACKET
                sub edx,1
                .endc .ifnz
                shr eax,4
                inc eax
                .continue(01)
              .case T_STRING
                push edx
                mov  edx,[ecx+eax].string_ptr
                .if byte ptr [edx] != '<'
                    mov edx,[ecx+eax].tokpos
                    .if byte ptr [edx] == '<'
                        pop eax
                        asmerr(7008, edx)
                        .break
                    .endif
                .endif
                pop edx
            .endsw
            shr eax,4
            inc eax
        .endw
    .until 1
    xor eax,eax
    ret

DelayExpand ENDP

    END
