; XMSTOREUSHORTN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreUShortN2 proc vectorcall pDestination:ptr XMUSHORTN2, V:FXMVECTOR

    inl_XMStoreUShortN2(rcx, xmm1)
    ret

XMStoreUShortN2 endp

    end
