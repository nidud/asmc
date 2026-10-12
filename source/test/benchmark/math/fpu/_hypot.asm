.code

_hypot proc x:real8, y:real8
    fld     x
    fld     st(0)
    fmulp
    fld     y
    fld     st(0)
    fmulp
    faddp
    fsqrt
    fstp    x
    movsd   xmm0,x
    ret
    endp

    end
