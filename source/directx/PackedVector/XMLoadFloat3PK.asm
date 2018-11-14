; XMLOADFLOAT3PK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadFloat3PK proc vectorcall pSource:ptr XMFLOAT3PK

    inl_XMLoadFloat3PK(rcx)
    ret

XMLoadFloat3PK endp

    end
