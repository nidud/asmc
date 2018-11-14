; XMSTOREUSHORTN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUShortN4 proc vectorcall pDestination:ptr XMUSHORTN4, V:FXMVECTOR

    inl_XMStoreUShortN4(rcx, xmm1)
    ret

XMStoreUShortN4 endp

    end
