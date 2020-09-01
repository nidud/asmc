; XMLOADDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadDec4 proc vectorcall pSource:ptr XMDEC4

    inl_XMLoadDec4(rcx)
    ret

XMLoadDec4 endp

    end
