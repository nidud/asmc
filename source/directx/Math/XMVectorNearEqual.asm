
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorNearEqual proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, Epsilon:FXMVECTOR

    inl_XMVectorNearEqual(xmm0, xmm1, xmm2)
    ret

XMVectorNearEqual endp

    end
