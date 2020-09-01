; XMLOADHALF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp nosave

XMLoadHalf4 proc vectorcall pSource:ptr XMHALF4

    inl_XMLoadHalf4(rcx)
    ret

XMLoadHalf4 endp

    end
