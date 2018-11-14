; XMSTORESINT3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreSInt3 proc XM_CALLCONV pDestination:ptr XMINT3, V:FXMVECTOR

    .assert( rcx )

    inl_XMStoreSInt3([rcx], xmm1)
    ret

XMStoreSInt3 endp

    end
