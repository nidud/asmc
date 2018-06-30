
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorInBounds proc XM_CALLCONV V:FXMVECTOR, Bounds:FXMVECTOR

    inl_XMVectorInBounds(xmm0, xmm1)
    ret

XMVectorInBounds endp

    end
