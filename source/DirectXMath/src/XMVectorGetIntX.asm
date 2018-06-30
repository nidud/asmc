
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntX proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorGetIntX(xmm0)
    ret

XMVectorGetIntX endp

    end
