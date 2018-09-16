
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntZPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr uint32_t

    inl_XMVectorSetIntZPtr(xmm0, [rdx])
    ret

XMVectorSetIntZPtr endp

    end
