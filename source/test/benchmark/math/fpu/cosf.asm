.code

cosf proc x:real4
    fld   x
    fcos
    fstp  x
    movss xmm0,x
    ret
    endp

    end
