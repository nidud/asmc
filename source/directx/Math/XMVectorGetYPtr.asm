
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetYPtr proc XM_CALLCONV y:ptr float, V:FXMVECTOR

    inl_XMVectorGetYPtr([rcx], xmm1)
    ret

XMVectorGetYPtr endp

    end
