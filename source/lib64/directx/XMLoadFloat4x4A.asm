
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat4x4A proc XM_CALLCONV XMTHISPTR, pSource:ptr XMFLOAT4X4
if _XM_VECTORCALL_
    assume rcx:ptr XMFLOAT4X4
    inl_XMLoadFloat4x4A([rcx])
else
    assume rcx:ptr XMMATRIX
    assume rdx:ptr XMFLOAT4X4
    inl_XMLoadFloat4x4A([rdx], [rcx])
    mov rax,rcx
endif
    ret
XMLoadFloat4x4A endp

    end
