; XMSTOREFLOAT4A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat4A proc XM_CALLCONV pDestination:ptr XMFLOAT4, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat4A([rcx], xmm1)
    ret

XMStoreFloat4A endp

    end
