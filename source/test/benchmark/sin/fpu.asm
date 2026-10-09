option win64:3

.code

sin proc x:real8
    fld     x
    fsin
    fstp    x
    movsd   xmm0,x
    ret
    endp

    end
