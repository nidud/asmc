; XMLOADCOLOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadColor proc vectorcall pSource:ptr XMCOLOR

    inl_XMLoadColor(rcx)
    ret

XMLoadColor endp

    end
