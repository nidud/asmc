; XMSTOREFLOAT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat2 proc XM_CALLCONV pDestination:ptr XMFLOAT2, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat2([rcx], xmm1)
    ret

XMStoreFloat2 endp

    end
