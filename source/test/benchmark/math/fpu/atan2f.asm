.code

atan2f proc y:real4, x:real4
    fld y
    fld x
    fpatan
    fstp y
    movss xmm0,y
    ret
    endp

    end
