
include quadmath.inc

    .code

acosqf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
    fstp    x

    LDTOXQFLOAT(x)
    ret

acosqf endp

    end
