; FLOORF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp noauto

floorf proc x:float

    movss       xmm1,1.0
    movss       xmm2,xmm0
    cvttps2dq   xmm0,xmm0
    cvtdq2ps    xmm0,xmm0
    cmpltps     xmm2,xmm0
    andps       xmm2,xmm1
    subss       xmm0,xmm2
    ret

floorf endp

    end
