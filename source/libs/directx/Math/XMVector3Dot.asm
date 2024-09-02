; XMVECTOR3DOT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVector3Dot proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR
ifdef _XM_SSE4_INTRINSICS_
    _mm_dp_ps(xmm0, xmm1, 0x7f)
elseifdef _XM_SSE3_INTRINSICS_
    _mm_mul_ps(xmm0, xmm1)
    _mm_and_ps(xmm0, g_XMMask3)
    _mm_hadd_ps(xmm0, xmm0)
    _mm_hadd_ps(xmm0, xmm0)
else
    _mm_mul_ps(xmm0, xmm1)
    _mm_store_ps(xmm1, xmm0)
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(2,1,2,1))
    _mm_add_ss(xmm0, xmm1)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(1,1,1,1))
    _mm_add_ss(xmm0, xmm1)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0,0,0,0))
endif
    ret

XMVector3Dot endp

    end
