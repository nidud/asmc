; XMLOADXDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadXDecN4 proc vectorcall pSource:ptr XMXDECN4

    inl_XMLoadXDecN4(rcx)
    ret

XMLoadXDecN4 endp

    end
