; XMLOADSHORTN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadShortN2 proc vectorcall pSource:ptr XMSHORTN2

    inl_XMLoadShortN2(rcx)
    ret

XMLoadShortN2 endp

    end
