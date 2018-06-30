
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntZ proc XM_CALLCONV V:FXMVECTOR, x:uint32_t

    inl_XMVectorSetIntZ(xmm0, edx)
    ret

XMVectorSetIntZ endp

    end
