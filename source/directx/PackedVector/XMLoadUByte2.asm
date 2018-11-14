; XMLOADUBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUByte2 proc vectorcall pSource:ptr XMUBYTE2

    inl_XMLoadUByte2(rcx)
    ret

XMLoadUByte2 endp

    end
