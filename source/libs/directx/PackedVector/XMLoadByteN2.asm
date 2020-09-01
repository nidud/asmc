; XMLOADBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadByteN2 proc vectorcall pSource:ptr XMBYTEN2

    inl_XMLoadByteN2(rcx)
    ret

XMLoadByteN2 endp

    end
