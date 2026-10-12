; _FABSF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

_fabsf proc x:float
ifdef _WIN64
    andps xmm0,_mm_set1_ps(0x7FFFFFFF)
else
    fld x
    fabs
endif
    ret
    endp

    end
