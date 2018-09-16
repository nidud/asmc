
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreSInt3 proc XM_CALLCONV pDestination:ptr XMINT3, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreSInt3([rcx], xmm1)
    ret

XMStoreSInt3 endp

    end
