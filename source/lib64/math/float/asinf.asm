
include math.inc

    .code

    option win64:rsp nosave noauto

asinf proc x:float

    cvtss2sd xmm0,xmm0
    asin(xmm0)
    cvtsd2ss xmm0,xmm0
    ret

asinf endp

    end
