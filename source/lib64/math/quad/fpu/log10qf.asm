
include quadmath.inc

    .code

log10qf proc vectorcall Q:XQFLOAT

  local x:REAL10

    XQFLOATTOLD(x)

    fld x
    fldlg2
    fxch st(1)
    fyl2x
    fstp x

    LDTOXQFLOAT(x)
    ret

log10qf endp

    end
