; LOGQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

logqf proc vectorcall Q:real16

  local x:REAL10

    _mm_cvtq_ld(x)

    fld x
    fldln2
    fxch st(1)
    fyl2x
    fstp x

    _mm_cvtld_q(x)
    ret

logqf endp

    end
