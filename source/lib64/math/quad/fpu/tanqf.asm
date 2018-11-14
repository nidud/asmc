; TANQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

tanqf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld  x
    fptan
    fstp st
    fstp x

    LDTOXQFLOAT(x)
    ret

tanqf endp

    end
