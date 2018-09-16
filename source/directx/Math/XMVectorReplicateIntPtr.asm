
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReplicateIntPtr proc XM_CALLCONV pValue:ptr uint32_t

    inl_XMVectorReplicateIntPtr(rcx)
    ret

XMVectorReplicateIntPtr endp

    end
