; ACOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

acos proc x:double

    movsd  xmm1,xmm0
    movsd  xmm2,xmm0
    movsd  xmm0,1.0
    mulsd  xmm2,xmm2
    subsd  xmm0,xmm2
    sqrtpd xmm0,xmm0
    jmp    atan2

acos endp

    end
