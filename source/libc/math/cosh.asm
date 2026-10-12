; COSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
option comdat:on
endif

.code

cosh proc x:double
ifdef _WIN64
    exp(_mm_and_pd(xmm0, _mm_set1_pd(0x7FFFFFFFFFFFFFFF)))
    _mm_div_sd(_mm_move_sd(xmm1, 1.0), xmm0)
    _mm_div_sd(_mm_add_sd(xmm0, xmm1), 2.0)
else
    fld     x
    fldl2e
    fmul    st(0),st(1)
    fld     st(0)
    frndint
    fsub    st(1),st(0)
    fxch    st(1)
    f2xm1
    fld1
    faddp   st(1),st(0)
    fscale
    fst     st(1)
    fld1
    fdivrp  st(1),st(0)
    faddp   st(1),st(0)
    fld1
    fadd    st(0),st(0)
    fdivp   st(1),st(0)
    fxch    st(1)
    fstp    st(0)
endif
    ret
    endp

    end
