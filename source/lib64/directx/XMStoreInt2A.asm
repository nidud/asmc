
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreInt2A proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreInt2A([rcx], xmm1)
    ret

XMStoreInt2A endp

    end
