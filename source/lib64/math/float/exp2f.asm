
include math.inc

    .code

    option win64:rsp nosave noauto

exp2f proc x:float

    cvtss2sd xmm0,xmm0
    exp2(xmm0)
    cvtsd2ss xmm0,xmm0
    ret

exp2f endp

    end
