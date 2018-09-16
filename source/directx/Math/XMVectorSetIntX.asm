
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntX proc XM_CALLCONV V:FXMVECTOR, x:uint32_t

    inl_XMVectorSetIntX(xmm0, edx)
    ret

XMVectorSetIntX endp

    end
