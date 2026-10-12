.code

asinf proc x:real4
    fld     x
    fld     st(0)
    fmul    st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan
    fstp    x
    movss   xmm0,x
    ret
    endp

    end
