; XMLOADUSHORTN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUShortN2 proc vectorcall pSource:ptr XMUSHORTN2

    inl_XMLoadUShortN2(rcx)
    ret

XMLoadUShortN2 endp

    end
