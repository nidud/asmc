; XMLOADSHORT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadShort2 proc vectorcall pSource:ptr XMSHORT2

    inl_XMLoadShort2(rcx)
    ret

XMLoadShort2 endp

    end
