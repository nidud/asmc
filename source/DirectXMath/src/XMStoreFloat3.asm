
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat3 proc XM_CALLCONV pDestination:ptr XMFLOAT3, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat3([rcx], xmm1)
    ret

XMStoreFloat3 endp

    end
