
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat proc XM_CALLCONV pDestination:ptr float, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat([rcx], xmm1)
    ret

XMStoreFloat endp

    end
