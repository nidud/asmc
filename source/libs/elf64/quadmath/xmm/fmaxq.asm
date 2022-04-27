; FMAXQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

fmaxq proc A:real16, B:real16

    .ifsd cmpq(xmm0, xmm1) == -1

        movaps xmm0,xmm1
    .endif
    ret

fmaxq endp

    end
