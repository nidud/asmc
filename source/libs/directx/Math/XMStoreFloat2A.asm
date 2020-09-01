; XMSTOREFLOAT2A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat2A proc XM_CALLCONV pDestination:ptr XMFLOAT2, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat2A([rcx], xmm1)
    ret

XMStoreFloat2A endp

    end
