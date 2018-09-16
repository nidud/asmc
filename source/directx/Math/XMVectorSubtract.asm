
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSubtract proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorSubtract(xmm0, xmm1)
    ret

XMVectorSubtract endp

    end
