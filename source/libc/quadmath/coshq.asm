; COSHQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

coshq proc x:real16
ifdef __SSE__
    movaps xmm2,expq(fabsq(xmm0))
    divq(addq(xmm2, divq(1.0, xmm2)), 2.0)
else
    int     3
endif
    ret
coshq endp

    end
