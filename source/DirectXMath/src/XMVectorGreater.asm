
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGreater proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorGreater(xmm0, xmm1)
    ret

XMVectorGreater endp

    end
