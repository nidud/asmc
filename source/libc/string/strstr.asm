; STRSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strstr proc uses rsi rdi rbx dst:LPSTR, src:LPSTR

ifdef _WIN64
    mov rdi,rcx
    mov rbx,rdx
else
    mov edi,dst
    mov ebx,src
endif

    .if strlen(rbx)

        mov rsi,rax

        .if strlen(rdi)

            mov rcx,rax
            xor eax,eax
            dec rsi

            .repeat

                mov     al,[rbx]
                repne   scasb
                mov     al,0

                .break .ifnz

                .if rsi

                    .break .if ( rcx < rsi )

                    mov rdx,rsi

                    .repeat

                        mov al,[rbx+rdx]

                        .continue(01) .if ( al != [rdi+rdx-1] )
                        dec rdx
                    .untilz

                .endif

                lea rax,[rdi-1]
            .until 1
        .endif
    .endif
    ret

strstr endp

    end
