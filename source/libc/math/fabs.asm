; _FABS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

_fabs proc x:double
ifdef _WIN64
    andpd xmm0,g_X2IABSMASK
else
    fld x
    fabs
endif
    ret
    endp

    end
