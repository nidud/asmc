; SINQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

sinqf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld x
    fsin
    fstp x

    LDTOXQFLOAT(x)
    ret

sinqf endp

    end
