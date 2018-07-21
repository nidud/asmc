
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
