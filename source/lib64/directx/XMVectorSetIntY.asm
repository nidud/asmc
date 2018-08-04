
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntY proc XM_CALLCONV V:FXMVECTOR, x:uint32_t

    inl_XMVectorSetIntY(xmm0, edx)
    ret

XMVectorSetIntY endp

    end
