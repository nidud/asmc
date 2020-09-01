; XMSTOREUDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUDecN4 proc vectorcall pDestination:ptr XMUDECN4, V:FXMVECTOR

    inl_XMStoreUDecN4(rcx, xmm1)
    ret

XMStoreUDecN4 endp

    end
