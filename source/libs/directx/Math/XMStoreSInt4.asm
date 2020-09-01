; XMSTORESINT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreSInt4 proc XM_CALLCONV pDestination:ptr XMINT4, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreSInt4([rcx], xmm1)
    ret

XMStoreSInt4 endp

    end
