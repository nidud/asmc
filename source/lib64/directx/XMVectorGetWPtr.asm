
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetWPtr proc XM_CALLCONV y:ptr float, V:FXMVECTOR

    inl_XMVectorGetWPtr([rcx], xmm1)
    ret

XMVectorGetWPtr endp

    end
