; XMSTOREINT2A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreInt2A proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_storel_epi64([rcx], xmm1)
    ret

XMStoreInt2A endp

    end
