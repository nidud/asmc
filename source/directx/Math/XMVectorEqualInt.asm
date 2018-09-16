
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorEqualInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorEqualInt(xmm0, xmm1)
    ret

XMVectorEqualInt endp

    end
