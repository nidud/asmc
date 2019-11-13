; ATAN2QF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

atan2qf proc vectorcall Y:real16, X:real16

  local y:REAL10
  local x:REAL10

    _mm_cvtq_ld(y)
    _mm_cvtq_ld(x, xmm1)

    fld     y
    fld     x
    fpatan
    fstp    x

    _mm_cvtld_q(x)
    ret

atan2qf endp

    end
