
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetYPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr float

    inl_XMVectorSetYPtr(xmm0, [rdx])
    ret

XMVectorSetYPtr endp

    end
