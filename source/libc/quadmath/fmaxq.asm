; FMAXQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

fmaxq proc a:real16, b:real16
ifdef _WIN64
    .ifd cmpq(xmm0, xmm1) == -1
        movaps xmm0,xmm1
    .endif
endif
    ret
fmaxq endp

    end
