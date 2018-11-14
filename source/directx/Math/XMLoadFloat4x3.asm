; XMLOADFLOAT4X3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat4x3 proc XM_CALLCONV XMTHISPTR, pSource:ptr XMFLOAT4X3
if _XM_VECTORCALL_
    inl_XMLoadFloat4x3([rcx])
else
    assume rcx:ptr XMMATRIX
    inl_XMLoadFloat4x3([rdx], [rcx])
    mov rax,rcx
endif
    ret
XMLoadFloat4x3 endp

    end
