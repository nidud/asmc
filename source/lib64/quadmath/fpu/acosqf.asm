; ACOSQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

acosqf proc vectorcall Q:real16

  local x:real10

    _mm_cvtq_ld(x)

    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
    fstp    x

    _mm_cvtld_q(x)
    ret

acosqf endp

    end
