
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat4x3 proc XM_CALLCONV pDestination:ptr XMFLOAT4X3, AXMMATRIX
if _XM_VECTORCALL_
    inl_XMStoreFloat4x3([rcx])
else
    assume rdx:ptr XMMATRIX
    inl_XMStoreFloat4x3([rcx],[rdx])
endif
    ret

XMStoreFloat4x3 endp

    end
