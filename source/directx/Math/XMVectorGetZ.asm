
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetZ proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetZ(xmm0)
    ret

XMVectorGetZ endp

    end
