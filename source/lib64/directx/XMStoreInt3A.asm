
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreInt3A proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreInt3A([rcx], xmm1)
    ret

XMStoreInt3A endp

    end
