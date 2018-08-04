
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorNotEqualInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorNotEqualInt(xmm0, xmm1)
    ret

XMVectorNotEqualInt endp

    end
