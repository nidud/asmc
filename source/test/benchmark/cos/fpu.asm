option win64:3

.code

cos proc x:real8
    fld   x
    fcos
    fstp  x
    movsd xmm0,x
    ret
    endp

    end
