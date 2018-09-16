
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetXPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr float

    inl_XMVectorSetXPtr(xmm0, [rdx])
    ret

XMVectorSetXPtr endp

    end
