
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
