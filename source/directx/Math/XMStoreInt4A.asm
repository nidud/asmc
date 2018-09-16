
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreInt4A proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreInt4A([rcx], xmm1)
    ret

XMStoreInt4A endp

    end
