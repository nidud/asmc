
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorTruncate proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorTruncate(xmm0)
    ret

XMVectorTruncate endp

    end
