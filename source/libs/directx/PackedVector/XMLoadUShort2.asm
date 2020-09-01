; XMLOADUSHORT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUShort2 proc vectorcall pSource:ptr XMUSHORT2

    inl_XMLoadUShort2(rcx)
    ret

XMLoadUShort2 endp

    end
