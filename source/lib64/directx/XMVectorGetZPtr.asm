
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetZPtr proc XM_CALLCONV y:ptr float, V:FXMVECTOR

    inl_XMVectorGetZPtr([rcx], xmm1)
    ret

XMVectorGetZPtr endp

    end
