; XMSTORESHORTN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreShortN2 proc vectorcall pDestination:ptr XMSHORTN2, V:FXMVECTOR

    inl_XMStoreShortN2(rcx, xmm1)
    ret

XMStoreShortN2 endp

    end
