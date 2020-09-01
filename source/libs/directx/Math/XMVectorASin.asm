; XMVECTORASIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorASin proc XM_CALLCONV V:FXMVECTOR

    _mm_cmpge_ps(xmm1, xmm0, _mm_setzero_ps(xmm2))
    _mm_sub_ps(xmm2, xmm0)
    _mm_max_ps(xmm0, xmm2)

    ;; Compute (1-|V|), clamp to zero to avoid sqrt of negative number.

    _mm_sub_ps(_mm_store_ps(xmm2, g_XMOne), xmm0)
    _mm_sqrt_ps(_mm_max_ps(_mm_setzero_ps(xmm3), xmm2))

    ;; Compute polynomial approximation

    _mm_store_ps(xmm4, _mm_store_ps(xmm2, g_XMArcCoefficients1))
    _mm_store_ps(xmm5, xmm2)
    _mm_mul_ps(XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(3, 3, 3, 3)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm5, _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_store_ps(xmm5, xmm4)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm5, _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm4, _MM_SHUFFLE(0, 0, 0, 0))), xmm0)

    _mm_store_ps(xmm4, _mm_store_ps(xmm5, g_XMArcCoefficients0))
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm5, _MM_SHUFFLE(3, 3, 3, 3))), xmm0)
    _mm_store_ps(xmm5, xmm4)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm5, _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_store_ps(xmm5, xmm4)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm5, _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, XM_PERMUTE_PS(xmm4, _MM_SHUFFLE(0, 0, 0, 0))), xmm3)

    _mm_store_ps(xmm0, g_XMPi)
    _mm_store_ps(xmm3, xmm1)

    _mm_sub_ps(xmm0, xmm2)
    _mm_and_ps(xmm3, xmm2)
    _mm_andnot_ps(xmm1, xmm0)
    _mm_or_ps(xmm3, xmm1)
    _mm_store_ps(xmm0, g_XMHalfPi)
    _mm_sub_ps(xmm0, xmm3)
    ret

XMVectorASin endp

    end
