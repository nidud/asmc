
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreUInt3 proc XM_CALLCONV pDestination:ptr XMUINT3, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreUInt3([rcx], xmm1)
    ret

XMStoreUInt3 endp

    end
