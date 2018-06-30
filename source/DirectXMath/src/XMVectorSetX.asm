
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetX proc XM_CALLCONV V:FXMVECTOR, x:float

    inl_XMVectorSetX(xmm0, xmm1)
    ret

XMVectorSetX endp

    end
