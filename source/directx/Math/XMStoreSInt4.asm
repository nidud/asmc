
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreSInt4 proc XM_CALLCONV pDestination:ptr XMINT4, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreSInt4([rcx], xmm1)
    ret

XMStoreSInt4 endp

    end
