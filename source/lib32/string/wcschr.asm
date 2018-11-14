; WCSCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcschr proc s1:ptr wchar_t, w:wchar_t

    xor eax,eax
    mov ecx,s1
    .repeat

        mov ax,[ecx]
        .break .if !eax

        add ecx,2
        .continue(0) .if ax != w

        lea eax,[ecx-2]
    .until 1
    ret

wcschr endp

    end
