; SINH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_sinh2
alias <__vdecl_sinh2>=<sinh>
assume uses xmm6 xmm7
endif

.code

sinh proc x:double
ifdef _WIN64
    _mm_mul_ps(xmm0, g_X4FLOG2E)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm3, g_X4FNEGONE)
    _mm_add_ps(xmm0, xmm3)
    _mm_sub_ps(xmm3, xmm1)
    _mm_store_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, _mm_exp2_ps(xmm3))
    _mm_exp2_ps(xmm6)
    _mm_sub_ps(xmm0, xmm7)
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
    fsubp   st(1),st(0)
    fld1
    fadd    st(0),st(0)
    fdivp   st(1),st(0)
    fxch    st(1)
    fstp    st(0)
endif
    ret
    endp

    end
