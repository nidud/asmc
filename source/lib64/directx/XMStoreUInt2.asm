
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreUInt2 proc XM_CALLCONV pDestination:ptr XMUINT2, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreUInt2([rcx], xmm1)
    ret

XMStoreUInt2 endp

    end
