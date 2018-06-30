
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorIsInfinite proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorIsInfinite(xmm0)
    ret

XMVectorIsInfinite endp

    end
