
include math.inc

    .code

    option win64:rsp nosave noauto

copysign proc number:double, _sign:double

    pcmpeqw xmm2,xmm2
    psrlq   xmm2,1
    andpd   xmm0,xmm2
    andnpd  xmm2,xmm1
    orpd    xmm0,xmm2
    ret

copysign endp

    end
