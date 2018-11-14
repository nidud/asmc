; STRSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strstr proc uses rsi rdi dst:LPSTR, src:LPSTR

    mov rdi,rcx
    .if strlen(rdx)
        mov rsi,rax
        .if strlen(rdi)
            mov rcx,rax
            xor eax,eax
            dec rsi
            .repeat
                mov al,[rdx]
                repne scasb
                mov al,0
                .break .ifnz
                .if rsi
                    .break .if rcx < rsi
                    mov r11,rsi
                    .repeat
                        mov al,[rdx+r11]
                        .continue(01) .if al != [rdi+r11-1]
                        dec r11
                    .untilz
                .endif
                lea rax,[rdi-1]
            .until 1
        .endif
    .endif
    ret

strstr endp

    END
