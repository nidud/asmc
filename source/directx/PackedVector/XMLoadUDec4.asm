; XMLOADUDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUDec4 proc vectorcall pSource:ptr XMUDEC4

    inl_XMLoadUDec4(rcx)
    ret

XMLoadUDec4 endp

    end
