; COSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc

define g_X2FTWO <{ 2.0, 2.0 }>

undef __vdecl_cosh2
alias <__vdecl_cosh2>=<cosh>
endif

.code

cosh proc x:double
ifdef _WIN64
    _mm_exp_pd(_mm_and_pd(xmm0, g_X2IABSMASK))
    _mm_move_pd(xmm1, g_X2FONE)
    _mm_div_pd(xmm1, xmm0)
    _mm_add_pd(xmm0, xmm1)
    _mm_div_pd(xmm0, g_X2FTWO)
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
