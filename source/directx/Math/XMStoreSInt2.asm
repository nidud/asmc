
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreSInt2 proc XM_CALLCONV pDestination:ptr XMINT2, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreSInt2([rcx], xmm1)
    ret

XMStoreSInt2 endp

    end
