; XMSTOREUDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUDec4 proc vectorcall pDestination:ptr XMUDEC4, V:FXMVECTOR

    inl_XMStoreUDec4(rcx, xmm1)
    ret

XMStoreUDec4 endp

    end
