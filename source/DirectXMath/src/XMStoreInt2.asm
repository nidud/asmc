
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreInt2 proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreInt2([rcx], xmm1)
    ret

XMStoreInt2 endp

    end
