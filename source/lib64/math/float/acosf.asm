
include math.inc

    .code

    option win64:rsp nosave noauto

acosf proc x:float

    cvtss2sd xmm0,xmm0
    acos(xmm0)
    cvtsd2ss xmm0,xmm0
    ret

acosf endp

    end
