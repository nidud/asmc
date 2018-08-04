
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSinEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSinEst(xmm0)
    ret

XMVectorSinEst endp

    end
