
include quadmath.inc

    .code

fmodqf proc vectorcall X:XQFLOAT, Y:XQFLOAT

  local x:REAL10
  local y:REAL10

    XQFLOATTOLD(x)
    XQFLOATTOLD(y, xmm1)

    fld x
    fld y
    fxch st(1)
    .repeat
        fprem
        fstsw ax
        sahf
    .untilnp
    fstp st(1)
    fstp x

    LDTOXQFLOAT(x)
    ret

fmodqf endp

    end
