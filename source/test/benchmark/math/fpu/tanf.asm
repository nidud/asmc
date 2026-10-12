.code

tanf proc x:real4
    fld     x
    fptan
    fstp    st(0)
    fstp    x
    movss   xmm0,x
    ret
    endp

    end
