
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat4A proc XM_CALLCONV pDestination:ptr XMFLOAT4, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat4A([rcx], xmm1)
    ret

XMStoreFloat4A endp

    end
