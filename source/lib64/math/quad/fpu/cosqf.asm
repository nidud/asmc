; COSQF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

cosqf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld  x
    fcos
    fstp x

    LDTOXQFLOAT(x)
    ret

cosqf endp

    end
