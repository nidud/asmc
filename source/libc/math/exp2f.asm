; EXP2F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

exp2f proc x:float
ifdef _WIN64
    cvtss2sd xmm0,xmm0
    exp2(xmm0)
    cvtsd2ss xmm0,xmm0
else
    int 3
endif
    ret
exp2f endp

    end
