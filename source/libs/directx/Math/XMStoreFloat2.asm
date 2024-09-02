; XMSTOREFLOAT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat2 proc XM_CALLCONV pDestination:ptr XMFLOAT2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_store_ps(xmm0, xmm1)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(1, 1, 1, 1))
    _mm_store_ss([rcx][0], xmm0)
    _mm_store_ss([rcx][4], xmm1)
    ret

XMStoreFloat2 endp

    end
