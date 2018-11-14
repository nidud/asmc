; MSLOOP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

msloop proc

    .repeat
        mousep()
    .untilz
    ret

msloop endp

    END
