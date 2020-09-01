; XMLOADUBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUByteN2 proc vectorcall pSource:ptr XMUBYTEN2

    inl_XMLoadUByteN2(rcx)
    ret

XMLoadUByteN2 endp

    end
