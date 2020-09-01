; XMLOADUNIBBLE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUNibble4 proc vectorcall pSource:ptr XMUNIBBLE4

    inl_XMLoadUNibble4(rcx)
    ret

XMLoadUNibble4 endp

    end
