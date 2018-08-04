
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat4x4A proc XM_CALLCONV pDestination:ptr XMFLOAT4X4, AXMMATRIX
if _XM_VECTORCALL_
    inl_XMStoreFloat4x4A([rcx])
else
    assume rdx:ptr XMMATRIX
    inl_XMStoreFloat4x4A([rcx],[rdx])
endif
    ret
XMStoreFloat4x4A endp

    end
