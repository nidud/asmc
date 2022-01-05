; WCSCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto nosave

wcscmp proc a:wstring_t, b:wstring_t

    mov eax,0xFF

    .repeat

        .break .if !eax

        mov ax,[rcx]
        add rcx,2
        cmp ax,[rdx]
        lea rdx,[rdx+2]
        .continue(0) .ifz
        sbb al,al
        sbb al,-1
    .until 1
    movsx eax,al
    ret

wcscmp endp

    end
