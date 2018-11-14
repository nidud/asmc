; XMCONVERTHALFTOFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMConvertHalfToFloat proc Value:HALF

    inl_XMConvertHalfToFloat(xmm0)
    ret

XMConvertHalfToFloat endp

    end
