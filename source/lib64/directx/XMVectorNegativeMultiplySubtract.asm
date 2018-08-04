
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorNegativeMultiplySubtract proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, V3:FXMVECTOR

    inl_XMVectorNegativeMultiplySubtract(xmm0, xmm1, xmm2)
    ret

XMVectorNegativeMultiplySubtract endp

    end
