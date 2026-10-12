.code

_hypotf proc x:real4, y:real4
    fld     x
    fld     st(0)
    fmulp
    fld     y
    fld     st(0)
    fmulp
    faddp
    fsqrt
    fstp    x
    movss   xmm0,x
    ret
    endp

    end
