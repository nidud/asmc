; XMLOADUBYTEN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUByteN4 proc vectorcall pSource:ptr XMUBYTEN4

    inl_XMLoadUByteN4(rcx)
    ret

XMLoadUByteN4 endp

    end
