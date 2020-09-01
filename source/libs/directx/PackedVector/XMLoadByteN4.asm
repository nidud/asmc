; XMLOADBYTEN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadByteN4 proc vectorcall pSource:ptr XMBYTEN4

    inl_XMLoadByteN4(rcx)
    ret

XMLoadByteN4 endp

    end
