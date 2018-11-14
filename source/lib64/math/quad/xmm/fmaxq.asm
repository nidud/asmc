; FMAXQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

fmaxq proc vectorcall A:XQFLOAT, B:XQFLOAT

    .ifsd cmpq(xmm0, xmm1) == -1

        movaps xmm0,xmm1
    .endif
    ret

fmaxq endp

    end
