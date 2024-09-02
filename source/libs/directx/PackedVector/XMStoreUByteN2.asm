; XMSTOREUBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreUByteN2 proc XM_CALLCONV pDestination:ptr XMUBYTEN2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    XMVectorSaturate(xmm0)
    XMVectorMultiplyAdd(xmm0, _mm_get_epi32(255.0, 255.0, 255.0, 255.0), g_XMOneHalf)
    XMVectorTruncate(xmm0)
    _mm_cvtps_epi32(xmm0)
    movq rdx,xmm0
    mov [rcx].XMUBYTEN2.x,dl
    shr rdx,32
    mov [rcx].XMUBYTEN2.y,dl
    ret

XMStoreUByteN2 endp

    end
