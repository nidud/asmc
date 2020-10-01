; _MBSPBRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

_mbspbrk proc uses rdi s1:LPSTR, s2:LPSTR

    mov     r8,rcx
    mov     rdi,rdx
    or      ecx,-1
    xor     eax,eax
    repnz   scasb
    not     ecx
    dec     ecx

    .return .ifz

    .for r9d = ecx, al = [r8] : eax : r8++

        mov   rdi,rdx
        repnz scasb
        mov   ecx,r9d

        .return r8 .ifz

        mov al,[r8+1]
    .endf
    xor eax,eax
    ret

_mbspbrk endp

    END
