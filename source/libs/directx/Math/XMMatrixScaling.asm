; XMMATRIXSCALING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .data

    x XMFLOAT4 { 1.0, 0.0, 0.0, 0.0 }
    y XMFLOAT4 { 0.0, 1.0, 0.0, 0.0 }
    z XMFLOAT4 { 0.0, 0.0, 1.0, 0.0 }

    .code

XMMatrixScaling proc XM_CALLCONV ScaleX:float, ScaleY:float, ScaleZ:float

    movss x.x,xmm0
    movss y.y,xmm1
    movss z.z,xmm2

    _mm_store_ps(xmm0, x)
    _mm_store_ps(xmm1, y)
    _mm_store_ps(xmm2, z)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
    ret

XMMatrixScaling endp

    end
