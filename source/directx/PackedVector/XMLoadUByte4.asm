; XMLOADUBYTE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadUByte4 proc vectorcall pSource:ptr XMUBYTE4

    inl_XMLoadUByte4(rcx)
    ret

XMLoadUByte4 endp

    end
