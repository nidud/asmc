; SINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

sinf proc x:float
ifdef __SSE__
    cvtss2sd xmm0,xmm0
    sin(xmm0)
    cvtsd2ss xmm0,xmm0
else
    fld     x
    fsin
endif
    ret
sinf endp

    end
