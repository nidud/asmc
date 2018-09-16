
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorAdd proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorAdd(xmm0, xmm1)
    ret

XMVectorAdd endp

    end
