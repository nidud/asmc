; SINHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

sinhf proc x:float
ifdef __SSE__
    cvtss2sd xmm0,xmm0
    sinh(xmm0)
    cvtsd2ss xmm0,xmm0
else
    int 3
endif
    ret
sinhf endp

    end
