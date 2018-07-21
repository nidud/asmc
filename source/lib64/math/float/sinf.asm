
include math.inc

    .code

    option win64:rsp nosave noauto

sinf proc x:float

    cvtss2sd xmm0,xmm0
    sin(xmm0)
    cvtsd2ss xmm0,xmm0
    ret

sinf endp

    end
