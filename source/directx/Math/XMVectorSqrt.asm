
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSqrt proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSqrt(xmm0)
    ret

XMVectorSqrt endp

    end
