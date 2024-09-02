; XMMATRIXLOOKATLH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixLookAtLH proc XM_CALLCONV EyePosition:FXMVECTOR, FocusPosition:FXMVECTOR, UpDirection:FXMVECTOR

    _mm_sub_ps(xmm1, xmm0)
    XMMatrixLookToLH(xmm0, xmm1, xmm2)
    ret

XMMatrixLookAtLH endp

    end
