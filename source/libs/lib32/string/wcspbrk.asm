; WCSPBRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcspbrk proc uses esi edi s1:LPWSTR, s2:LPWSTR

    xor eax,eax
    mov edi,s2
    or  ecx,-1
    repnz scasw
    not ecx
    dec ecx

    .repeat
        .break .ifz
        .for esi = s1, ax = [esi] : eax : esi += 2

            mov edi,s2
            mov edx,ecx
            repnz scasw
            mov ecx,edx
            .ifz
                mov eax,esi
                .break(1)
            .endif
            mov ax,[esi+2]
        .endf
        xor eax,eax
    .until 1
    ret

wcspbrk endp

    END
