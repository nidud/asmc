
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntY proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetIntY(xmm0)
    ret

XMVectorGetIntY endp

    end
