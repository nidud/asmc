; ATANQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

atanqf proc vectorcall Q:real16

  local x:REAL10

    _mm_cvtq_ld(x)

    fld     x
    fld1
    fpatan
    fstp    x

    _mm_cvtld_q(x)
    ret

atanqf endp

    end
