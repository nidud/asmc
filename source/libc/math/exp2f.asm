; EXP2F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

exp2f proc x:float
ifdef _WIN64
    powf(2.0, xmm0)
else
    powf(2.0, x)
endif
    ret

exp2f endp

    end
