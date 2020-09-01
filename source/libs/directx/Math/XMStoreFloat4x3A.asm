; XMSTOREFLOAT4X3A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat4x3A proc XM_CALLCONV pDestination:ptr XMFLOAT4X3, AXMMATRIX
if _XM_VECTORCALL_
    inl_XMStoreFloat4x3A([rcx])
else
    assume rdx:ptr XMMATRIX
    inl_XMStoreFloat4x3A([rcx],[rdx])
endif
    ret
XMStoreFloat4x3A endp

    end
