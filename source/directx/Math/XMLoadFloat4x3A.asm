
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat4x3A proc XM_CALLCONV XMTHISPTR, pSource:ptr XMFLOAT4X3
if _XM_VECTORCALL_
    inl_XMLoadFloat4x3A([rcx])
else
    assume rcx:ptr XMMATRIX
    inl_XMLoadFloat4x3A([rdx], [rcx])
    mov rax,rcx
endif
    ret
XMLoadFloat4x3A endp

    end
