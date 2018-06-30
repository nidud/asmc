
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetY proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetY(xmm0)
    ret

XMVectorGetY endp

    end
