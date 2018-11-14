; _STRUPR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

strupr::
_strupr::

    mov rax,rcx
    .while 1
        mov dl,[rcx]
        .break .if !dl
        sub dl,'a'
        cmp dl,'Z' - 'A' + 1
        sbb dl,dl
        and dl,'a' - 'A'
        xor [rcx],dl
        inc rcx
    .endw
    ret

    END
