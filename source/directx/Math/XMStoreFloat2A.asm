
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat2A proc XM_CALLCONV pDestination:ptr XMFLOAT2, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat2A([rcx], xmm1)
    ret

XMStoreFloat2A endp

    end
