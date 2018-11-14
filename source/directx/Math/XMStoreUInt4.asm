; XMSTOREUINT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreUInt4 proc XM_CALLCONV pDestination:ptr XMUINT4, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreUInt4([rcx], xmm1)
    ret

XMStoreUInt4 endp

    end
