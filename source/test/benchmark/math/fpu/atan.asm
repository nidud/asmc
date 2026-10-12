.code

atan proc x:real8
    fld x
    fld1
    fpatan
    fstp x
    movsd xmm0,x
    ret
    endp

    end
