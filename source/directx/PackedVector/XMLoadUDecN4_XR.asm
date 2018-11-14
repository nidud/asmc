; XMLOADUDECN4_XR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUDecN4_XR proc vectorcall pSource:ptr XMUDECN4

    inl_XMLoadUDecN4_XR(rcx)
    ret

XMLoadUDecN4_XR endp

    end
