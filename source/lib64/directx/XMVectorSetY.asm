
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetY proc XM_CALLCONV V:FXMVECTOR, x:float

    inl_XMVectorSetY(xmm0, xmm1)
    ret

XMVectorSetY endp

    end
