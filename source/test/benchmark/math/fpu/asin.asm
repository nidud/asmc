.code

asin proc x:real8
    fld     x
    fld     st(0)
    fmul    st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan
    fstp    x
    movsd   xmm0,x
    ret
    endp

    end
