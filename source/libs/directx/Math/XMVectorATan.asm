; XMVECTORATAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorATan proc XM_CALLCONV V:FXMVECTOR

    _mm_store_ps(xmm3, g_XMOne)
    _mm_cmpgt_ps(xmm2, xmm0, xmm3)
    _mm_store_ps(xmm1, xmm2)
    _mm_and_ps(xmm1, xmm3)
    _mm_andnot_ps(xmm2, g_XMNegativeOne)
    _mm_or_ps(xmm2, xmm1)
    _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(xmm5), xmm0), xmm0)
    _mm_cmple_ps(xmm5, xmm3)
    _mm_store_ps(xmm1, xmm5)
    _mm_store_ps(xmm4, xmm5)
    _mm_andnot_ps(xmm5, xmm2)
    _mm_and_ps(xmm1, xmm0)
    _mm_andnot_ps(xmm4, _mm_div_ps(xmm3, xmm0))
    _mm_or_ps(xmm1, xmm4)
    _mm_mul_ps(_mm_store_ps(xmm0, xmm1), xmm0)

    ;; Compute polynomial approximation

    _mm_store_ps(xmm3, _mm_store_ps(xmm2, g_XMATanCoefficients1))
    _mm_mul_ps(XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(3, 3, 3, 3)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(0, 0, 0, 0))), xmm0)
    _mm_store_ps(xmm3, g_XMATanCoefficients0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(3, 3, 3, 3))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(0, 0, 0, 0))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, g_XMOne), xmm1)
    _mm_store_ps(xmm0, xmm5)
    _mm_sub_ps(_mm_mul_ps(xmm5, g_XMHalfPi), xmm2)

    _mm_cmpeq_ps(xmm0, _mm_setzero_ps(xmm3))
    _mm_store_ps(xmm3, xmm0)
    _mm_and_ps(xmm0, xmm2)
    _mm_andnot_ps(xmm3, xmm5)
    _mm_or_ps(xmm0, xmm3)
    ret

XMVectorATan endp

    end
