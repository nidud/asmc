
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreInt3 proc XM_CALLCONV pDestination:ptr uint32_t, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreInt3([rcx], xmm1)
    ret

XMStoreInt3 endp

    end
