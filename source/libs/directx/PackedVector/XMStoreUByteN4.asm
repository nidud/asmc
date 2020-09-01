; XMSTOREUBYTEN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUByteN4 proc vectorcall pDestination:ptr XMUBYTEN4, V:FXMVECTOR

    inl_XMStoreUByteN4(rcx, xmm1)
    ret

XMStoreUByteN4 endp

    end
