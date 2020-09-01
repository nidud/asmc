; ISASCII.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

isascii::

    mov     eax,ecx
    and     eax,0x80
    setz    al
    ret

    end

