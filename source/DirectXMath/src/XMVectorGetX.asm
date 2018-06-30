
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetX proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetX(xmm0)
    ret

XMVectorGetX endp

    end
