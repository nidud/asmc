; ACOSQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

acosq proc q:real16
ifdef _WIN64
    movaps xmm4,xmm0
    atan2q(sqrtq(subq(1.0, mulq(xmm0, xmm0))), xmm4)
else
    int 3
endif
    ret
acosq endp

    end
