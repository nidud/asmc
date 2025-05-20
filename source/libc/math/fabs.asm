; _FABS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

_fabs proc x:double
ifdef _WIN64
    pcmpeqw xmm1,xmm1
    psrlq   xmm1,1
    andpd   xmm0,xmm1
else
    fld     x
    fabs
endif
    ret

_fabs endp

    end
