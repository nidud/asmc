; LOG.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

log proc x:double

    fld x
    fldln2
    fxch st(1)
    fyl2x
    ret

log endp

    end
