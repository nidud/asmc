
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntYPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr uint32_t

    inl_XMVectorSetIntYPtr(xmm0, [rdx])
    ret

XMVectorSetIntYPtr endp

    end
