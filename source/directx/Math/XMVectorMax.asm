
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorMax proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorMax(xmm0, xmm1)
    ret

XMVectorMax endp

    end
