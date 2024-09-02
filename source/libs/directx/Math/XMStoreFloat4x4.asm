; XMSTOREFLOAT4X4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat4x4 proc XM_CALLCONV pDestination:ptr XMFLOAT4X4, V0:XMVECTOR, V1:XMVECTOR, V2:XMVECTOR, V3:XMVECTOR

    ldr rcx,pDestination
    ldr xmm4,V3
    ldr xmm3,V2
    ldr xmm2,V1
    ldr xmm1,V0

    _mm_storeu_ps([rcx][0x00], xmm0)
    _mm_storeu_ps([rcx][0x10], xmm1)
    _mm_storeu_ps([rcx][0x20], xmm2)
    _mm_storeu_ps([rcx][0x30], xmm3)
    ret

XMStoreFloat4x4 endp

    end
