; XMVECTORSQRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSqrt proc XM_CALLCONV V:FXMVECTOR

    _mm_sqrt_ps(xmm0)
    ret

XMVectorSqrt endp

    end
