; XMVECTOR3NORMALIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVector3Normalize proc XM_CALLCONV V:FXMVECTOR

    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm2, _mm_mul_ps(xmm1, xmm0))
    _mm_shuffle_ps(xmm2, xmm1, _MM_SHUFFLE(2,1,2,1))
    _mm_add_ss(xmm1, xmm2)
    _mm_add_ss(xmm1, XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(1,1,1,1)))
    _mm_setzero_ps(xmm2)
    _mm_sqrt_ps(xmm3, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,0,0,0)))
    _mm_cmpneq_ps(xmm1, g_XMInfinity)
    _mm_div_ps(xmm0, xmm3)
    _mm_cmpneq_ps(xmm2, xmm3)
    _mm_and_ps(xmm0, xmm2)
    _mm_andnot_ps(_mm_store_ps(xmm2, xmm1), g_XMQNaN)
    _mm_and_ps(xmm1, xmm0)
    _mm_or_ps(_mm_store_ps(xmm0, xmm2), xmm1)
    ret

XMVector3Normalize endp

    end
