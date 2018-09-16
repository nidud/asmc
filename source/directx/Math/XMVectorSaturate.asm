
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSaturate proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSaturate(xmm0)
    ret

XMVectorSaturate endp

    end
