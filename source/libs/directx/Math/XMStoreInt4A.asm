; XMSTOREINT4A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreInt4A proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_store_si128([rcx], xmm1)
    ret

XMStoreInt4A endp

    end
