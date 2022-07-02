; TANHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

tanhf proc x:float
ifdef _WIN64
    cvtss2sd xmm0,xmm0
    tanh(xmm0)
    cvtsd2ss xmm0,xmm0
else
    int 3
endif
    ret
tanhf endp

    end
