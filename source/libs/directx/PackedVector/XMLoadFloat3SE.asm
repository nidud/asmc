; XMLOADFLOAT3SE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadFloat3SE proc vectorcall pSource:ptr XMFLOAT3SE

    inl_XMLoadFloat3SE(rcx)
    ret

XMLoadFloat3SE endp

    end
