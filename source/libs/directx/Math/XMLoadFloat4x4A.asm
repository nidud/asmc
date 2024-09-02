; XMLOADFLOAT4X4A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadFloat4x4A proc XM_CALLCONV pSource:ptr XMFLOAT4X4

    ldr rcx,pSource

    _mm_load_ps(xmm0, xmmword ptr [rcx].XMFLOAT4X4._11)
    _mm_load_ps(xmm1, xmmword ptr [rcx].XMFLOAT4X4._21)
    _mm_load_ps(xmm2, xmmword ptr [rcx].XMFLOAT4X4._31)
    _mm_load_ps(xmm3, xmmword ptr [rcx].XMFLOAT4X4._41)
    ret

XMLoadFloat4x4A endp

    end
