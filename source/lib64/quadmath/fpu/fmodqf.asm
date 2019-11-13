; FMODQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

fmodqf proc vectorcall X:real16, Y:real16

  local x:REAL10
  local y:REAL10

    _mm_cvtq_ld(x)
    _mm_cvtq_ld(y, xmm1)

    fld x
    fld y
    fxch st(1)
    .repeat
        fprem
        fstsw ax
        sahf
    .untilnp
    fstp st(1)
    fstp x

    _mm_cvtld_q(x)
    ret

fmodqf endp

    end
