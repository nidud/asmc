; XMSTORESHORT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreShort2 proc vectorcall pDestination:ptr XMSHORT2, V:FXMVECTOR

    inl_XMStoreShort2(rcx, xmm1)
    ret

XMStoreShort2 endp

    end
