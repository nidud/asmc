
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntZPtr proc XM_CALLCONV x:ptr uint32_t, V:FXMVECTOR

    inl_XMVectorGetIntZPtr(rcx, xmm1)
    ret

XMVectorGetIntZPtr endp

    end
