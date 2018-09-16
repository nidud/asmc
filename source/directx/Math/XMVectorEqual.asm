
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorEqual proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorEqual(xmm0, xmm1)
    ret

XMVectorEqual endp

    end
