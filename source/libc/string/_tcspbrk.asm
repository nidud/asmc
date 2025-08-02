; _TCSPBRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strpbrk(const char *str, const char *strCharSet);
; wchar_t *wcspbrk(wchar_t *str, const wchar_t *strCharSet);
;
; Scans strings for characters in specified character sets.
;
include string.inc
include tchar.inc

    .code

_tcspbrk proc uses rsi rdi rbx string:tstring_t, CharSet:tstring_t

    ldr     rcx,string
    ldr     rdx,CharSet

    mov     rbx,rcx
    mov     rdi,rdx

    xor     ecx,ecx
    xor     eax,eax
    dec     rcx
    repnz   _tscasb
    not     rcx
    dec     rcx
   .return .ifz

    .for ( rsi = rcx, _tal = [rbx] : eax : rbx += tchar_t, _tal = [rbx] )

        mov rdi,rdx
        mov rcx,rsi
        repnz _tscasb
        .ifz
            .return( rbx )
        .endif
    .endf
    .return( NULL )

_tcspbrk endp

    end
