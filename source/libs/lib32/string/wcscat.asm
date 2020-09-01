; WCSCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcscat proc uses esi edi s1:LPWSTR, s2:LPWSTR

    xor eax,eax
    mov edi,s1
    mov esi,s2
    mov ecx,-1
    repne scasw
    sub edi,2

    .repeat

        mov ax,[esi]
        mov [edi],ax
        add edi,2
        add esi,2
    .until !eax

    mov eax,s1
    ret

wcscat endp

    end
