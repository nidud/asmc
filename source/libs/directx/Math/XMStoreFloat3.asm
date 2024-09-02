; XMSTOREFLOAT3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat3 proc XM_CALLCONV pDestination:ptr XMFLOAT3, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_store_ps(xmm0, xmm1)
    _mm_store_ps(xmm2, xmm1)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(1, 1, 1, 1))
    XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(2, 2, 2, 2))
    _mm_store_ss([rcx][0], xmm0)
    _mm_store_ss([rcx][4], xmm1)
    _mm_store_ss([rcx][8], xmm2)
    ret

XMStoreFloat3 endp

    end
