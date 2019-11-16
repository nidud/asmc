; WCSPBRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcspbrk proc s1:LPWSTR, s2:LPWSTR

    mov r8,rcx
    mov r9,rdi

    xor eax,eax
    mov rdi,rdx
    mov rcx,-1
    repnz scasw
    not rcx
    dec rcx
    mov rdi,r9
    .return .ifz

    .for ax = [r8] : eax : r8 += 2

        mov rdi,rdx
        mov r10d,ecx
        repnz scasw
        mov rdi,r9
        mov ecx,r10d
        .return r8 .ifz
        mov ax,[r8+2]
    .endf
    xor eax,eax
    ret

wcspbrk endp

    END
