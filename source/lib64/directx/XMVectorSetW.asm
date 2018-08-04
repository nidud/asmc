
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetW proc XM_CALLCONV V:FXMVECTOR, x:float

    inl_XMVectorSetW(xmm0, xmm1)
    ret

XMVectorSetW endp

    end
