; ASIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

asin proc _x:double
ifdef _WIN64
   .new x:double = xmm0
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
    movsd   xmm0,x
endif
    ret

asin endp

    end
