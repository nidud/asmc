
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVector3Normalize proc XM_CALLCONV V:FXMVECTOR

    inl_XMVector3Normalize(xmm0)
    ret

XMVector3Normalize endp

    end
