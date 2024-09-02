; XMSTOREINT3A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreInt3A proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    _mm_storel_epi64([rcx][0], xmm0)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(2, 2, 2, 2))
    _mm_store_ss([rcx][8], xmm0)
    ret

XMStoreInt3A endp

    end
