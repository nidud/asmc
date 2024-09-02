; XMMATRIXLOOKATRH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixLookAtRH proc XM_CALLCONV EyePosition:FXMVECTOR, FocusPosition:FXMVECTOR, UpDirection:FXMVECTOR

    _mm_store_ps(xmm3, xmm0)
    XMVectorSubtract(xmm0, xmm1)
    XMMatrixLookToLH(xmm0, xmm3, xmm2)
    ret

XMMatrixLookAtRH endp

    end
