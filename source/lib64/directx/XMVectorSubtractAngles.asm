
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSubtractAngles proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorSubtractAngles(xmm0, xmm1)
    ret

XMVectorSubtractAngles endp

    end
