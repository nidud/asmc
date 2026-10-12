.code

atanf proc x:real4
    fld x
    fld1
    fpatan
    fstp x
    movss xmm0,x
    ret
    endp

    end
