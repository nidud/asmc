; XMSTOREFLOAT2A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat2A proc XM_CALLCONV pDestination:ptr XMFLOAT2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_storel_epi64([rcx], xmm1)
    ret

XMStoreFloat2A endp

    end
