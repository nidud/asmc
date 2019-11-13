; SQRTQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

sqrtqf proc vectorcall Q:real16

  local x:REAL10

    _mm_cvtq_ld(x)

    fld x
    fsqrt
    fstp x

    _mm_cvtld_q(x)
    ret

sqrtqf endp

    end
