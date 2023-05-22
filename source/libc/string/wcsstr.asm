; WCSSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcsstr proc uses rsi rdi rbx dst:wstring_t, src:wstring_t

    ldr rdi,dst
    ldr rbx,src

    .if wcslen(rbx)

        mov rsi,rax
        .if wcslen(rdi)

            mov rcx,rax
            xor eax,eax
            dec rsi

            .repeat

                mov     ax,[rbx]
                repne   scasw
                mov     ax,0

                .break .ifnz

                .if rsi

                    .break .if ( rcx < rsi )

                    mov rdx,rsi
                    .repeat

                        mov ax,[rbx+rdx*2]

                        .continue(01) .if ( ax != [rdi+rdx*2-2] )
                        sub rdx,1
                    .untilz
                .endif
                lea rax,[rdi-2]
            .until 1
        .endif
    .endif
    ret

wcsstr endp

    end
