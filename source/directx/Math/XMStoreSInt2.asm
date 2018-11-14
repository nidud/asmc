; XMSTORESINT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreSInt2 proc XM_CALLCONV pDestination:ptr XMINT2, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreSInt2([rcx], xmm1)
    ret

XMStoreSInt2 endp

    end
