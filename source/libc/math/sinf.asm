; SINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc

undef __vdecl_sinf4
alias <__vdecl_sinf4>=<sinf>

define g_X4FSINCOEFFICIENTS0    <{ -0.16666667, +0.0083333310, -0.00019840874, +2.7525562e-06 }>
define g_X4FSINCOEFFICIENTS1    <{ -2.3889859e-08, -0.16665852, +0.0083139502, -0.00018524670 }>
endif

.code

sinf proc x:float
ifdef _WIN64
    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm0, g_X4FRECIPROCALTWOPI)
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm_mul_ps(xmm0, g_X4FTWOPI)
    _mm_sub_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm1)

    _mm_and_ps(xmm1, g_X4FNEGZERO)
    _mm_store_ps(xmm2, xmm1)
    _mm_or_ps(xmm2, g_X4FPI)
    _mm_store_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm3, xmm0)
    _mm_sub_ps(xmm2, xmm0)
    _mm_cmple_ps(xmm3, g_X4FPI_2)
    _mm_and_ps(xmm0, xmm3)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_or_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm1, xmm0)
    _mm_store_ps(xmm3, g_X4FSINCOEFFICIENTS1)
    _mm_store_ps(xmm2, _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm3, g_X4FSINCOEFFICIENTS0)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(3,3,3,3)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(2,2,2,2)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(1,1,1,1)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, g_X4FONE)
    _mm_mul_ps(xmm0, xmm2)
else
    fld x
    fsin
endif
    ret
    endp

    end
