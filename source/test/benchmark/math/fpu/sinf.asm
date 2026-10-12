.code

sinf proc x:real4
    fld     x
    fsin
    fstp    x
    movss   xmm0,x
    ret
    endp

    end
