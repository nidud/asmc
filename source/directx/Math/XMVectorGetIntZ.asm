
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntZ proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetIntZ(xmm0)
    ret

XMVectorGetIntZ endp

    end
