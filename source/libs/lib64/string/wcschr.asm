; WCSCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcschr proc s1:ptr wchar_t, w:wchar_t

    xor eax,eax
    .repeat

        mov ax,[rcx]
        .break .if !eax

        add rcx,2
        .continue(0) .if ax != dx

        lea rax,[rcx-2]
    .until 1
    ret

wcschr endp

    end
