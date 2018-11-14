; WCSCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

wcscmp::

    mov eax,0xFFFF

    .repeat

        .break .if !eax

        mov ax,[rdx]
        add rdx,2
        cmp ax,[rcx]
        lea rcx,[rcx+2]
        .continue(0) .ifz
        sbb ax,ax
        sbb ax,-1
    .until 1
    movsx eax,ax
    ret

    END
