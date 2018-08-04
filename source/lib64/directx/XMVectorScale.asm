
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorScale proc XM_CALLCONV V:FXMVECTOR, ScaleFactor:float

    inl_XMVectorScale(xmm0, xmm1)
    ret

XMVectorScale endp

    end
