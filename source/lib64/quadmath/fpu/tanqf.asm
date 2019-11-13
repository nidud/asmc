; TANQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

tanqf proc vectorcall Q:real16

  local x:REAL10

    _mm_cvtq_ld(x)

    fld  x
    fptan
    fstp st
    fstp x

    _mm_cvtld_q(x)
    ret

tanqf endp

    end
