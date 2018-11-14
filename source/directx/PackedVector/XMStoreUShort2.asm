; XMSTOREUSHORT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUShort2 proc vectorcall pDestination:ptr XMUSHORT2, V:FXMVECTOR

    inl_XMStoreUShort2(rcx, xmm1)
    ret

XMStoreUShort2 endp

    end
