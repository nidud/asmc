.code

atan2 proc y:real8, x:real8
    fld y
    fld x
    fpatan
    fstp y
    movsd xmm0,y
    ret
    endp

    end
