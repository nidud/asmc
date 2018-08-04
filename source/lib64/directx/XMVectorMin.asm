
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorMin proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorMin(xmm0, xmm1)
    ret

XMVectorMin endp

    end
