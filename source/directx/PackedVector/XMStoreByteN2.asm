; XMSTOREBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreByteN2 proc vectorcall pSource:ptr XMBYTEN2, V:FXMVECTOR

    inl_XMStoreByteN2(rcx, xmm1)
    ret

XMStoreByteN2 endp

    end
