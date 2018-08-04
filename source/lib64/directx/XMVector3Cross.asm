
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVector3Cross proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVector3Cross(xmm0, xmm1)
    ret

XMVector3Cross endp

    end
