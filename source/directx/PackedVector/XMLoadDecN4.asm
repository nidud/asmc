; XMLOADDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadDecN4 proc vectorcall pSource:ptr XMDECN4

    inl_XMLoadDecN4(rcx)
    ret

XMLoadDecN4 endp

    end
