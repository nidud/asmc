; LOG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
