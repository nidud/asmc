
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntYPtr proc XM_CALLCONV x:ptr uint32_t, V:FXMVECTOR

    inl_XMVectorGetIntYPtr(rcx, xmm1)
    ret

XMVectorGetIntYPtr endp

    end
