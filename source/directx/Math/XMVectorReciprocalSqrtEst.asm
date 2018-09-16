
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReciprocalSqrtEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorReciprocalSqrtEst(xmm0)
    ret

XMVectorReciprocalSqrtEst endp

    end
