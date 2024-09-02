; XMVECTORCEILING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXMath.inc

    .code

XMVectorCeiling proc XM_CALLCONV V:FXMVECTOR
ifdef _XM_SSE4_INTRINSICS_
    _mm_ceil_ps(xmm0)
else
    _mm_store_ps(xmm1, g_XMAbsMask)
    _mm_store_ps(xmm3, g_XMNoFraction)
    _mm_cvttps_epi32(xmm2, xmm0)
    _mm_and_ps(xmm1, xmm0)
    pcmpgtd xmm3,xmm1
    _mm_cvtepi32_ps(xmm1, xmm2)
    _mm_store_ps(xmm2, xmm1)
    cmpltps xmm2, xmm0
    _mm_store_ps(xmm4, xmm3)
    cvtdq2ps xmm2, xmm2
    _mm_sub_ps(xmm1, xmm2)
    _mm_andnot_si128(xmm4, xmm0)
    _mm_store_ps(xmm0, xmm4)
    _mm_and_ps(xmm1, xmm3)
    _mm_or_ps(xmm0, xmm1)
endif
    ret

XMVectorCeiling endp

    end
