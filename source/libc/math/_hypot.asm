; _HYPOT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

.code

_hypot proc x:double, y:double
ifdef _WIN64
    mulsd   xmm0,xmm0
    mulsd   xmm1,xmm1
    addsd   xmm0,xmm1
    sqrtsd  xmm0,xmm0
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
