; XMSTOREFLOAT3PK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat3PK proc vectorcall pDestination:ptr XMFLOAT3PK, V:FXMVECTOR

    inl_XMStoreFloat3PK(rcx, xmm1)
    ret

XMStoreFloat3PK endp

    end
