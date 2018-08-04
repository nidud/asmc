
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorACos proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorACos(xmm0)
    ret

XMVectorACos endp

    end
