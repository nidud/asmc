; ASINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

asinf proc _x:float
ifdef _WIN64
   .new x:float = xmm0
else
    define x _x
endif
    fld     x
    fld     st(0)
    fmul    st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan
ifdef _WIN64
    fstp    x
    movss   xmm0,x
endif
    ret

asinf endp

    end
