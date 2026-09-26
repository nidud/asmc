; ASINF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_asinf4
alias <__vdecl_asinf4>=<asinf>
endif

.code

asinf proc x:float
ifdef _WIN64
    _mm_cmpge_ps(xmm1, xmm0, _mm_setzero_ps(xmm2))
    _mm_sub_ps(xmm2, xmm0)
    _mm_max_ps(xmm0, xmm2)

    _mm_sub_ps(_mm_store_ps(xmm2, g_X4FONE), xmm0)
    _mm_sqrt_ps(_mm_max_ps(_mm_setzero_ps(xmm3), xmm2))

    _mm_store_ps(xmm4, _mm_store_ps(xmm2, g_X4FARCCOEFFICIENTS1))
    _mm_store_ps(xmm5, xmm2)
    _mm_mul_ps(_mm_permute_ps(xmm2, _MM_SHUFFLE(3, 3, 3, 3)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm5, _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_store_ps(xmm5, xmm4)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm5, _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm4, _MM_SHUFFLE(0, 0, 0, 0))), xmm0)

    _mm_store_ps(xmm4, _mm_store_ps(xmm5, g_X4FARCCOEFFICIENTS0))
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm5, _MM_SHUFFLE(3, 3, 3, 3))), xmm0)
    _mm_store_ps(xmm5, xmm4)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm5, _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_store_ps(xmm5, xmm4)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm5, _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm4, _MM_SHUFFLE(0, 0, 0, 0))), xmm3)

    _mm_store_ps(xmm0, g_X4FPI)
    _mm_store_ps(xmm3, xmm1)

    _mm_sub_ps(xmm0, xmm2)
    _mm_and_ps(xmm3, xmm2)
    _mm_andnot_ps(xmm1, xmm0)
    _mm_or_ps(xmm3, xmm1)
    _mm_store_ps(xmm0, g_X4FPI_2)
    _mm_sub_ps(xmm0, xmm3)
else
    fld     x
    fld     st(0)
    fmul    st(1),st(0)
    fld1
    fsubr
    fsqrt
    fpatan
endif
    ret
    endp

    end
