; XMSTORESHORTN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreShortN4 proc vectorcall pDestination:ptr XMSHORTN4, V:FXMVECTOR

    inl_XMStoreShortN4(rcx, xmm1)
    ret

XMStoreShortN4 endp

    end
