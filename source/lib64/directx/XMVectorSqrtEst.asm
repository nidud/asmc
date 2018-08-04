
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSqrtEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSqrtEst(xmm0)
    ret

XMVectorSqrtEst endp

    end
