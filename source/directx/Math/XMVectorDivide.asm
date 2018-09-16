
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorDivide proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorDivide(xmm0, xmm1)
    ret

XMVectorDivide endp

    end
