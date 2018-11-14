; XMSTOREFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat proc XM_CALLCONV pDestination:ptr float, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreFloat([rcx], xmm1)
    ret

XMStoreFloat endp

    end
