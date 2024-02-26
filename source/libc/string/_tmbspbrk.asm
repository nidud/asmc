; _TMBSPBRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcspbrk proc uses rsi rdi rbx s1:LPTSTR, s2:LPTSTR

    ldr     rcx,s1
    ldr     rdx,s2
    mov     rbx,rcx
    xor     eax,eax
    mov     rdi,rdx
    mov     ecx,-1
    repnz  .scasb
    not     ecx
    dec     ecx
   .return .ifz

    .for ( esi = ecx, __a = [rbx] : eax : rbx += TCHAR, __a = [rbx] )

        mov rdi,rdx
        mov ecx,esi
        repnz .scasb
        .ifz
            .return( rbx )
        .endif
    .endf
    .return( NULL )

_tcspbrk endp

    end
