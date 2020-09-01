; ISPRINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

isprint::

    mov eax,ecx
    .if al < 0x20 || al >= 0x7F

        xor eax,eax
    .endif
    ret

    end

