; ATAN2QF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

atan2qf proc Y:real16, X:real16

    fldq()
    fldq(d, xmm1)
    fpatan
    fstq()
    ret

atan2qf endp

    end
