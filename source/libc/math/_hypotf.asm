; _HYPOTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

_hypotf proc x:float, y:float
ifdef _WIN64
    mulss   xmm0,xmm0
    mulss   xmm1,xmm1
    addss   xmm0,xmm1
    sqrtss  xmm0,xmm0
else
    fld     x
    fld     x
    fmulp
    fld     y
    fld     y
    fmulp
    faddp
    fsqrt
endif
    ret
    endp

    end
