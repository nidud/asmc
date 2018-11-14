; XMSTORESHORT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreShort4 proc vectorcall pDestination:ptr XMSHORT4, V:FXMVECTOR

    inl_XMStoreShort4(rcx, xmm1)
    ret

XMStoreShort4 endp

    end
