; XMVECTORTRUNCATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorTruncate proc XM_CALLCONV V:FXMVECTOR
ifdef _XM_SSE4_INTRINSICS_
    _mm_round_ps(xmm0, _MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC)
else
    _mm_store_ps(xmm1, g_XMAbsMask)
    _mm_store_ps(xmm2, g_XMNoFraction)
    _mm_and_ps(xmm1, xmm0)
    _mm_cmplt_epi32(xmm2, xmm1, xmm2) ; reverse..
    _mm_cvttps_epi32(xmm1, xmm0)
    _mm_cvtepi32_ps(xmm1)
    _mm_store_ps(xmm3, xmm2)
    _mm_and_ps(xmm1, xmm2)
    _mm_andnot_si128(xmm3, xmm0)
    _mm_store_ps(xmm0, xmm3)
    _mm_or_ps(xmm0, xmm1)
endif
    ret

XMVectorTruncate endp

    end
