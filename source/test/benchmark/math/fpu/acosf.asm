.code

acosf proc x:real4
    fld     x
    fmul    st(0),st(0)
    fld1
    fsubrp  st(1),st(0)
    fsqrt
    fld     x
    fpatan
    fstp    x
    movss   xmm0,x
    ret
    endp

    end
