; XMSTOREBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreByteN2 proc XM_CALLCONV pDestination:ptr XMBYTEN2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    XMVectorClamp(xmm0, g_XMNegativeOne, g_XMOne)
    XMVectorMultiply(xmm0, _mm_get_epi32(127.0, 127.0, 127.0, 127.0))
    XMVectorRound(xmm0)
    cvtps2dq xmm0,xmm0
    movq rdx,xmm0
    mov [rcx].XMBYTEN2.x,dl
    shr rdx,32
    mov [rcx].XMBYTEN2.y,dl
    ret

XMStoreByteN2 endp

    end
