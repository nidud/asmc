
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorAddAngles proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorAddAngles(xmm0, xmm1)
    ret

XMVectorAddAngles endp

    end
