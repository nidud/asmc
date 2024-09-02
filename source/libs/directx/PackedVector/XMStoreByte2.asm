; XMSTOREBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreByte2 proc XM_CALLCONV pDestination:ptr XMBYTE2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    _mm_store_ps(xmm1, _mm_get_epi32(-127.0, -127.0, -127.0, -127.0))
    _mm_store_ps(xmm2, _mm_get_epi32(127.0, 127.0, 127.0, 127.0))

    XMVectorClamp(xmm0, xmm1, xmm2)
    XMVectorRound(xmm0)
    _mm_cvtps_epi32(xmm0)
    movq rdx,xmm0
    mov [rcx].XMBYTE2.x,dl
    shr rdx,32
    mov [rcx].XMBYTE2.y,dl
    ret

XMStoreByte2 endp

    end
