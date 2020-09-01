; XMSTOREBYTEN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreByteN4 proc vectorcall pSource:ptr XMBYTEN4, V:FXMVECTOR

    inl_XMStoreByteN4(rcx, xmm1)
    ret

XMStoreByteN4 endp

    end
