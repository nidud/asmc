
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntWPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr uint32_t

    inl_XMVectorSetIntWPtr(xmm0, [rdx])
    ret

XMVectorSetIntWPtr endp

    end
