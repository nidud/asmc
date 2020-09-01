; XMLOADUSHORT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUShort4 proc vectorcall pSource:ptr XMUSHORT4

    inl_XMLoadUShort4(rcx)
    ret

XMLoadUShort4 endp

    end
