; _TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_toupper::

    movzx   eax,cl
    sub     al,'a'-'A'
    ret

    end

