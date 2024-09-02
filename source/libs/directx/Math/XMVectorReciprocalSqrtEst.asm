; XMVECTORRECIPROCALSQRTEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorReciprocalSqrtEst proc XM_CALLCONV V:FXMVECTOR

    _mm_rsqrt_ps(xmm0)
    ret

XMVectorReciprocalSqrtEst endp

    end
