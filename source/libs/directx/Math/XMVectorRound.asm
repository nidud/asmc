; XMVECTORROUND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorRound proc XM_CALLCONV V:FXMVECTOR
ifdef _XM_SSE4_INTRINSICS_
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
else
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm2, g_XMNegativeZero)
    _mm_store_ps(xmm3, g_XMAbsMask)
    _mm_and_ps(xmm2, xmm0)
    _mm_or_ps(xmm2, g_XMNoFraction)
    _mm_and_ps(xmm3, xmm0)
    _mm_cmple_ps(xmm3, g_XMNoFraction)
    _mm_store_ps(xmm0, xmm2)
    _mm_add_ps(xmm0, xmm1)
    _mm_sub_ps(xmm0, xmm2)
    _mm_and_ps(xmm0, xmm3)
    _mm_andnot_ps(xmm3, xmm1)
    _mm_xor_ps(xmm0, xmm3)
endif
    ret

XMVectorRound endp

    end
