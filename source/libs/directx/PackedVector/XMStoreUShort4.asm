; XMSTOREUSHORT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUShort4 proc vectorcall pDestination:ptr XMUSHORT4, V:FXMVECTOR

    inl_XMStoreUShort4(rcx, xmm1)
    ret

XMStoreUShort4 endp

    end
