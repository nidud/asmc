; XMSTOREUNIBBLE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUNibble4 proc vectorcall pDestination:ptr XMUNIBBLE4, V:FXMVECTOR

    inl_XMStoreUNibble4(rcx, xmm1)
    ret

XMStoreUNibble4 endp

    end
