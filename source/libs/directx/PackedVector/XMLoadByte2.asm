; XMLOADBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadByte2 proc vectorcall pSource:ptr XMBYTE2

    inl_XMLoadByte2(rcx)
    ret

XMLoadByte2 endp

    end
