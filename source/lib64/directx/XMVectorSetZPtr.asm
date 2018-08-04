
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetZPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr float

    inl_XMVectorSetZPtr(xmm0, [rdx])
    ret

XMVectorSetZPtr endp

    end
