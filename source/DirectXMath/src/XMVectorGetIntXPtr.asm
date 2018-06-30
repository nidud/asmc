
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntXPtr proc XM_CALLCONV x:ptr uint32_t, V:FXMVECTOR

    inl_XMVectorGetIntXPtr(rcx, xmm1)
    ret

XMVectorGetIntXPtr endp

    end
