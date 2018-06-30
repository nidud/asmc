
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorOrInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorOrInt(xmm0, xmm1)
    ret

XMVectorOrInt endp

    end
