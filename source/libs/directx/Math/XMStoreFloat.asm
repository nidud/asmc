; XMSTOREFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat proc XM_CALLCONV pDestination:ptr float, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_store_ss( [rcx], xmm1 )
    ret

XMStoreFloat endp

    end
