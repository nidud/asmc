
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReciprocalEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorReciprocalEst(xmm0)
    ret

XMVectorReciprocalEst endp

    end
