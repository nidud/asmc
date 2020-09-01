; XMSTOREUBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUByteN2 proc vectorcall pDestination:ptr XMUBYTEN2, V:FXMVECTOR

    inl_XMStoreUByteN2(rcx, xmm1)
    ret

XMStoreUByteN2 endp

    end
