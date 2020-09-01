; XMSTOREUINT3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreUInt3 proc XM_CALLCONV pDestination:ptr XMUINT3, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreUInt3([rcx], xmm1)
    ret

XMStoreUInt3 endp

    end
