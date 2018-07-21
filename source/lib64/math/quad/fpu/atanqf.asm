
include quadmath.inc

    .code

atanqf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld     x
    fld1
    fpatan
    fstp    x

    LDTOXQFLOAT(x)
    ret

atanqf endp

    end
