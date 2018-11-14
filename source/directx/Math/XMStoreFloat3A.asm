; XMSTOREFLOAT3A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat3A proc XM_CALLCONV pDestination:ptr XMFLOAT3, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat3A([rcx], xmm1)
    ret

XMStoreFloat3A endp

    end
