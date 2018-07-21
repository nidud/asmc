
include quadmath.inc

    .code

sqrtqf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld x
    fsqrt
    fstp x

    LDTOXQFLOAT(x)
    ret

sqrtqf endp

    end
