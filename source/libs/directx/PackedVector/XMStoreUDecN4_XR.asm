; XMSTOREUDECN4_XR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUDecN4_XR proc vectorcall pDestination:ptr XMUDECN4, V:FXMVECTOR

    inl_XMStoreUDecN4_XR(rcx, xmm1)
    ret

XMStoreUDecN4_XR endp

    end
