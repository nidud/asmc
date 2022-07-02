; _FABSF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

_fabsf proc x:float
ifdef __SSE__
    pcmpeqw xmm1,xmm1
    psrld   xmm1,1
    andps   xmm0,xmm1
else
    fld     x
    fabs
endif
    ret
_fabsf endp

    end
