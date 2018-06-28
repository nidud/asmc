
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreUInt4 proc XM_CALLCONV pDestination:ptr XMUINT4, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreUInt4([rcx], xmm1)
    ret

XMStoreUInt4 endp

    end
