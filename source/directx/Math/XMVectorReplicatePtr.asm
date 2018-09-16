
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReplicatePtr proc XM_CALLCONV pValue:ptr float

    inl_XMVectorReplicatePtr(rcx)
    ret

XMVectorReplicatePtr endp

    end
