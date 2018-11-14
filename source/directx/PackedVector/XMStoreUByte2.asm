; XMSTOREUBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUByte2 proc vectorcall pDestination:ptr XMUBYTE2, V:FXMVECTOR

    inl_XMStoreUByte2(rcx, xmm1)
    ret

XMStoreUByte2 endp

    end
