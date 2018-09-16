
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorModAngles proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorModAngles(xmm0)
    ret

XMVectorModAngles endp

    end
