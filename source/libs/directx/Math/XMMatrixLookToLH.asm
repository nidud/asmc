; XMMATRIXLOOKTOLH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixLookToLH proc XM_CALLCONV uses xmm6 xmm7 EyePosition:FXMVECTOR, EyeDirection:FXMVECTOR, UpDirection:FXMVECTOR

    _mm_store_ps(xmm4, xmm2)
    _mm_sub_ps(_mm_setzero_ps(xmm6), xmm0)
    XMVector3Normalize(xmm1)
    _mm_store_ps(xmm5, xmm0)
    XMVector3Cross(xmm4, xmm5)
    XMVector3Normalize(xmm0)
    _mm_store_ps(xmm4, xmm0)
    XMVector3Cross(xmm5, xmm4)
    _mm_store_ps(xmm3, xmm0)
    XMVector3Dot(xmm4, xmm6)
    _mm_store_ps(xmm7, xmm0)
    XMVector3Dot(xmm3, xmm6)
    _mm_store_ps(xmm2, xmm0)
    XMVector3Dot(xmm5, xmm6)
    _mm_store_ps(xmm6, xmm0)
    _mm_store_ps(xmm0, xmm2)
    XMVectorSelect(xmm0, xmm3, g_XMSelect1110.v)
    _mm_store_ps(xmm3, xmm0)
    XMVectorSelect(xmm7, xmm4, g_XMSelect1110.v)
    _mm_store_ps(xmm4, xmm0)
    XMVectorSelect(xmm6, xmm5, g_XMSelect1110.v)
    _mm_store_ps(xmm2, xmm0)
    _mm_store_ps(xmm1, xmm3)
    XMMatrixTranspose(xmm4, xmm1, xmm2, g_XMIdentityR3.v)
    ret

XMMatrixLookToLH endp

    end
