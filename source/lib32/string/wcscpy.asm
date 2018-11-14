; WCSCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcscpy proc uses esi edi ecx s1:LPWSTR, s2:LPWSTR

    sub eax,eax
    mov ecx,-1
    mov edi,s2
    repne scasw
    mov edi,s1
    mov esi,s2
    mov eax,edi
    not ecx
    rep movsw
    ret

wcscpy endp

    end
