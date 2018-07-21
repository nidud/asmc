
include math.inc
include xmmmacros.inc

    .code

    option win64:nosave

cosh proc x:REAL8

    exp(_fabs(xmm0))
    movsd xmm1,FLT8(1.0)
    divsd xmm1,xmm0
    addsd xmm0,xmm1
    divsd xmm0,FLT8(2.0)
    ret

cosh endp

    end
