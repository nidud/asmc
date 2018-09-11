
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
