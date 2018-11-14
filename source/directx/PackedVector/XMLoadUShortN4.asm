; XMLOADUSHORTN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUShortN4 proc vectorcall pSource:ptr XMUSHORTN4

    inl_XMLoadUShortN4(rcx)
    ret

XMLoadUShortN4 endp

    end
