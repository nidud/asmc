; XMVECTORRECIPROCALEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorReciprocalEst proc XM_CALLCONV V:FXMVECTOR

    _mm_rcp_ps(xmm0)
    ret

XMVectorReciprocalEst endp

    end
