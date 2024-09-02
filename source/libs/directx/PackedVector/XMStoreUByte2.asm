; XMSTOREUBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreUByte2 proc XM_CALLCONV pDestination:ptr XMUBYTE2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    XMVectorClamp(xmm0, _mm_setzero_ps(xmm1), _mm_get_epi32(255.0, 255.0, 255.0, 255.0))
    XMVectorRound(xmm0)
    _mm_cvtps_epi32(xmm0)
    movq rdx,xmm0
    mov [rcx].XMUBYTE2.x,dl
    shr rdx,32
    mov [rcx].XMUBYTE2.y,dl
    ret

XMStoreUByte2 endp

    end
