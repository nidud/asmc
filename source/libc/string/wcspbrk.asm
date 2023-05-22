; WCSPBRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcspbrk proc uses rsi rdi rbx s1:LPWSTR, s2:LPWSTR

    ldr     rcx,s1
    ldr     rdx,s2

    mov     rbx,rcx
    xor     eax,eax
    mov     rdi,rdx
    mov     ecx,-1
    repnz   scasw
    not     ecx
    dec     ecx

    .return .ifz

    .for ( esi = ecx, ax = [rbx] : eax : rbx += 2, ax = [rbx] )

        mov rdi,rdx
        mov ecx,esi
        repnz scasw
        .ifz
            .return( rbx )
        .endif
    .endf
    .return( NULL )

wcspbrk endp

    end
