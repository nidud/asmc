; XMLOADUDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUDecN4 proc vectorcall pSource:ptr XMUDECN4

    inl_XMLoadUDecN4(rcx)
    ret

XMLoadUDecN4 endp

    end
