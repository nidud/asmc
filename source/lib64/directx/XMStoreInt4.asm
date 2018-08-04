
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreInt4 proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreInt4([rcx], xmm1)
    ret

XMStoreInt4 endp

    end
