; _CVTBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.data
_cvtbuf string_t NULL

.code

_cvtbuf_init proc private

    mov _cvtbuf,malloc(_CVTBUFSIZE)
    ret

_cvtbuf_init endp

.pragma init(_cvtbuf_init, 90)

    end
