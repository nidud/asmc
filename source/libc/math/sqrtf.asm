; SQRTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

sqrtf proc x:float
ifdef __SSE__
    sqrtss  xmm0,xmm0
else
    fld     x
    fsqrt
endif
    ret

sqrtf endp

    end
