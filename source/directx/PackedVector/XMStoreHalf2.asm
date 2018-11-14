; XMSTOREHALF2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp nosave

XMStoreHalf2 proc vectorcall pDestination:ptr XMHALF2, V:FXMVECTOR

    inl_XMStoreHalf2(rcx, xmm1)
    ret

XMStoreHalf2 endp

    end
