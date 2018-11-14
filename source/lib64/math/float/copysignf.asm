; COPYSIGNF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

copysignf proc number:double, _sign:double

    pcmpeqw xmm2,xmm2
    psrld   xmm2,1
    andps   xmm0,xmm2
    andnps  xmm2,xmm1
    orps    xmm0,xmm2
    ret

copysignf endp

    end
