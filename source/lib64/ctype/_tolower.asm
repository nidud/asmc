; _TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_tolower::

    movzx   eax,cl
    sub     al,'A'
    add     al,'a'
    ret

    end