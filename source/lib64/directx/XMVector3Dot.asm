
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVector3Dot proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVector3Dot(xmm0, xmm1)
    ret

XMVector3Dot endp

    end
