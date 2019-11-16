; WCSNCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcsncat proc uses rsi rdi s1:LPWSTR, s2:LPWSTR, max:SIZE_T

    mov r9,rcx
    xor eax,eax
    mov rdi,rcx
    mov rsi,rdx
    mov ecx,-1
    repne scasw
    sub rdi,2
    .repeat

        .if !r8d

            mov [rdi],r8w
            .break
        .endif
        lodsw
        stosw
        dec r8d
    .until !eax
    mov rax,r9
    ret

wcsncat endp

    end
