; _MBSPBRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_mbspbrk proc uses rsi rdi rbx s1:string_t, s2:string_t
ifdef _WIN64
    mov     rsi,rcx
    mov     rdi,rdx
else
    mov     esi,s1
    mov     edi,s2
endif
    or      ecx,-1
    xor     eax,eax
    repnz   scasb
    not     ecx
    dec     ecx

    .return .ifz

    .for ( ebx = ecx, al = [rsi] : eax : rsi++ )

        mov   rdi,rdx
        repnz scasb
        mov   ecx,ebx

        .return rsi .ifz

        mov al,[rsi+1]
    .endf
    .return( 0 )

_mbspbrk endp

    end
