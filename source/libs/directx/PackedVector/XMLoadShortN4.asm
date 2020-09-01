; XMLOADSHORTN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadShortN4 proc vectorcall pSource:ptr XMSHORTN4

    inl_XMLoadShortN4(rcx)
    ret

XMLoadShortN4 endp

    end
