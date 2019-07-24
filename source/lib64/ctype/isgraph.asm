; ISGRAPH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

isgraph::

    mov eax,ecx
    .if al < 0x21 || al >= 0x7F

        xor eax,eax
    .endif
    ret

    end
