; XMSTOREFLOAT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat4 proc XM_CALLCONV pDestination:ptr XMFLOAT4, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat4([rcx], xmm1)
    ret

XMStoreFloat4 endp

    end
