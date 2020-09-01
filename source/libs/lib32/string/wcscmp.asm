; WCSCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcscmp proc uses esi edi s1:LPWSTR, s2:LPWSTR

    mov esi,s2
    mov edi,s1
    mov eax,1

    .repeat

        .break .if !eax

        mov cx,[esi]
        mov ax,[edi]
        add esi,2
        add edi,2
        .continue(0) .if ax == cx
        sbb eax,eax
        sbb eax,-1
    .until 1
    ret

wcscmp endp

    end
