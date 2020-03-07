; FMODQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

fmodqf proc vectorcall X:real16, Y:real16

    fldq()
    fldq(, xmm1)
    fxch st(1)
    .repeat
        fprem
        fstsw ax
        sahf
    .untilnp
    fstp st(1)
    fstq()
    ret

fmodqf endp

    end
