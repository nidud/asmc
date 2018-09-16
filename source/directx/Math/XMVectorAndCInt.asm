
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorAndCInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorAndCInt(xmm0, xmm1)
    ret

XMVectorAndCInt endp

    end
