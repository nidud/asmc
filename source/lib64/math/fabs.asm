
include math.inc

    .code

    option win64:rsp nosave noauto

_fabs proc x:double

    pcmpeqw xmm1,xmm1
    psrlq   xmm1,1
    andpd   xmm0,xmm1
    ret

_fabs endp

    end
