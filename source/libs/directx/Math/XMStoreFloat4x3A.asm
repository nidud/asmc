; XMSTOREFLOAT4X3A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat4x3A proc XM_CALLCONV pDestination:ptr XMFLOAT4X3, V0:XMVECTOR, V1:XMVECTOR, V2:XMVECTOR, V3:XMVECTOR

    ldr rcx,pDestination
    ldr xmm4,V3
    ldr xmm3,V2
    ldr xmm2,V1
    ldr xmm1,V0

    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_ps(xmm0, xmm2, _MM_SHUFFLE(1,0,2,2))
    _mm_shuffle_ps(xmm2, xmm3, _MM_SHUFFLE(1,0,2,1))
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(2,0,1,0))
    _mm_store_ps([rcx][0], xmm1)
    _mm_shuffle_ps(xmm3, xmm4, _MM_SHUFFLE(0,0,2,2))
    _mm_shuffle_ps(xmm3, xmm4, _MM_SHUFFLE(2,1,2,0))
    _mm_store_ps([rcx][16], xmm2)
    _mm_store_ps([rcx][32], xmm3)
    ret

XMStoreFloat4x3A endp

    end
