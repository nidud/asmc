; TANHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_tanhf4
alias <__vdecl_tanhf4>=<tanhf>
define Scale            <{ 2.8853900817779268, 2.8853900817779268, 2.8853900817779268, 2.8853900817779268 }>
define g_X4FONEHALF     <{ 0.5, 0.5, 0.5, 0.5 }>
endif

.code

tanhf proc x:float
ifdef _WIN64
    _mm_exp2_ps(_mm_mul_ps(xmm0, Scale))
    _mm_mul_ps(xmm0, g_X4FONEHALF)
    _mm_add_ps(xmm0, g_X4FONEHALF)
    _mm_store_ps(xmm1, g_X4FONE)
    _mm_store_ps(xmm2, xmm1)
    _mm_div_ps(xmm1, xmm0)
    _mm_sub_ps(xmm2, xmm1)
    _mm_store_ps(xmm0, xmm2)
else
    fld     x
    fldl2e
    fadd    st(0),st(0)
    fmulp   st(1),st(0)
    fld     st(0)
    frndint
    fsub    st(1),st(0)
    fxch    st(1)
    f2xm1
    fld1
    faddp   st(1),st(0)
    fscale
    fld1
    fsubp   st(1),st(0)
    fxch    st(1)
    fstp    st(0)
    fld     st(0)
    fld1
    fadd    st(0),st(0)
    faddp   st(1),st(0)
    fdivp   st(1),st(0)
    ret
endif
    ret
    endp

    end
