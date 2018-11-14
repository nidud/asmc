; XMLOADU555.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadU555 proc vectorcall pSource:ptr XMU555

    inl_XMLoadU555(rcx)
    ret

XMLoadU555 endp

    end
