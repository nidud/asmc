; XMSTOREFLOAT3A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat3A proc XM_CALLCONV pDestination:ptr XMFLOAT3, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    _mm_storel_epi64(qword ptr [rcx], xmm0)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(2, 2, 2, 2))
    _mm_store_ss([rcx][8], xmm0)
    ret

XMStoreFloat3A endp

    end
