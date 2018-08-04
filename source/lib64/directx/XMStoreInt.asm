
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreInt proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreInt([rcx], xmm1)
    ret

XMStoreInt endp

    end
