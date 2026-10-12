.code

tan proc x:real8
    fld     x
    fptan
    fstp    st(0)
    fstp    x
    movsd   xmm0,x
    ret
    endp

    end
