; LOG10QF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

log10qf proc vectorcall Q:real16

  local x:REAL10

    _mm_cvtq_ld(x)

    fld x
    fldlg2
    fxch st(1)
    fyl2x
    fstp x

    _mm_cvtld_q(x)
    ret

log10qf endp

    end
