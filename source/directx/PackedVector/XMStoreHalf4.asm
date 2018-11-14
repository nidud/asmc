; XMSTOREHALF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreHalf4 proc vectorcall pDestination:ptr XMHALF4, V:FXMVECTOR

    inl_XMStoreHalf4(rcx, xmm1)
    ret

XMStoreHalf4 endp

    end
