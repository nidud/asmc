; XMLOADXDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadXDec4 proc vectorcall pSource:ptr XMXDEC4

    inl_XMLoadXDec4(rcx)
    ret

XMLoadXDec4 endp

    end
