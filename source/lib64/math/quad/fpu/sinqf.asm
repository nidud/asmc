
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
