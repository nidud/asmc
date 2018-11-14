; LOGQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

logqf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld x
    fldln2
    fxch st(1)
    fyl2x
    fstp x

    LDTOXQFLOAT(x)
    ret

logqf endp

    end
