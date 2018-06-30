
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorXorInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorXorInt(xmm0, xmm1)
    ret

XMVectorXorInt endp

    end
