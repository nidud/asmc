; XMMATRIXSCALINGFROMVECTOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixScalingFromVector proc XM_CALLCONV Scale:FXMVECTOR

    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm2, xmm0)
    _mm_and_ps(xmm0, g_XMMaskX)
    _mm_and_ps(xmm1, g_XMMaskY)
    _mm_and_ps(xmm2, g_XMMaskZ)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
    ret

XMMatrixScalingFromVector endp

    end
