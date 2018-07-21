
include math.inc

    .code

    option win64:rsp nosave noauto

atan2f proc x:float, y:float

    cvtss2sd xmm0,xmm0
    cvtss2sd xmm1,xmm1
    atan2(xmm0, xmm1)
    cvtsd2ss xmm0,xmm0
    ret

atan2f endp

    end
