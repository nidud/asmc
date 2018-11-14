; XMSTOREFLOAT4X4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat4x4 proc XM_CALLCONV pDestination:ptr XMFLOAT4X4, AXMMATRIX
if _XM_VECTORCALL_
    inl_XMStoreFloat4x4([rcx])
else
    assume rdx:ptr XMMATRIX
    inl_XMStoreFloat4x4([rcx],[rdx])
endif
    ret
XMStoreFloat4x4 endp

    end
