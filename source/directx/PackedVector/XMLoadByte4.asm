; XMLOADBYTE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadByte4 proc vectorcall pSource:ptr XMBYTE4

    inl_XMLoadByte4(rcx)
    ret

XMLoadByte4 endp

    end
