; XMLOADU565.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMLoadU565 proc vectorcall pSource:ptr XMU565

    inl_XMLoadU565(rcx)
    ret

XMLoadU565 endp

    end
