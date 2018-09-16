
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorMultiply proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorMultiply(xmm0, xmm1)
    ret

XMVectorMultiply endp

    end
