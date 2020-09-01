; XMLOADHALF2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:nosave

XMLoadHalf2 proc vectorcall pSource:ptr XMHALF2

    inl_XMLoadHalf2(rcx)
    ret

XMLoadHalf2 endp

    end
