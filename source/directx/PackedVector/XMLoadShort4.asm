; XMLOADSHORT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadShort4 proc vectorcall pSource:ptr XMSHORT4

    inl_XMLoadShort4(rcx)
    ret

XMLoadShort4 endp

    end
