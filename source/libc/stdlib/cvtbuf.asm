; _CVTBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.data
_cvtbuf string_t NULL

.code

__initcvtbuf proc private

    mov _cvtbuf,malloc(_CVTBUFSIZE)
    ret

__initcvtbuf endp

.pragma init(__initcvtbuf, 90)

    end
