; XMVECTORMOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorMod proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR
ifdef _XM_SSE4_INTRINSICS_
    _mm_store_ps(xmm2, xmm0)
    _mm_div_ps(xmm2, xmm1)
    _mm_round_ps(xmm2, _MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC)
    _mm_mul_ps(xmm2, xmm1)
    _mm_sub_ps(xmm0, xmm2)
elseifdef _XM_SSE_INTRINSICS_
    _mm_store_ps(xmm2, xmm0)
    _mm_div_ps(xmm2, xmm1)
    _mm_store_ps(xmm3, g_XMAbsMask)
    _mm_store_ps(xmm4, g_XMNoFraction)
    _mm_and_ps(xmm3, xmm0)
    _mm_cmplt_epi32(xmm4, xmm3, xmm4)
    _mm_cvttps_epi32(xmm3, xmm0)
    _mm_cvtepi32_ps(xmm3)
    _mm_store_ps(xmm5, xmm4)
    _mm_and_ps(xmm3, xmm4)
    _mm_andnot_si128(xmm5, xmm2)
    _mm_store_ps(xmm2, xmm5)
    _mm_or_ps(xmm2, xmm3)
    _mm_mul_ps(xmm2, xmm1)
    _mm_sub_ps(xmm0, xmm2)
endif
    ret

XMVectorMod endp

    end
