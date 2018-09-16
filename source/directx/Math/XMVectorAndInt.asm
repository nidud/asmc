
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorAndInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorAndInt(xmm0, xmm1)
    ret

XMVectorAndInt endp

    end
