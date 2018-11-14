; WCSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcslen proc uses edi string:LPWSTR

    xor eax,eax
    mov edi,string
    or  ecx,-1
    repne scasw
    not ecx
    dec ecx
    mov eax,ecx
    ret

wcslen endp

    END
