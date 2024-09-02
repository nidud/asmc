; XMVECTORRECIPROCALSQRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorReciprocalSqrt proc XM_CALLCONV V:FXMVECTOR

    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, g_XMOne)
    _mm_div_ps(xmm0, xmm1)
    ret

XMVectorReciprocalSqrt endp

    end
