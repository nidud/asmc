; WCSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcslen proc uses rdi string:wstring_t

    ldr     rcx,string

    mov     rdi,rcx
    mov     ecx,-1
    xor     eax,eax
    repnz   scasw
    not     ecx
    dec     ecx
    mov     eax,ecx
    ret

wcslen endp

    end
