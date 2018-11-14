; XMSTOREUBYTE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUByte4 proc vectorcall pDestination:ptr XMUBYTE4, V:FXMVECTOR

    inl_XMStoreUByte4(rcx, xmm1)
    ret

XMStoreUByte4 endp

    end
