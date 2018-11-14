; XMCONVERTFLOATTOHALF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMConvertFloatToHalf proc Value:float

    inl_XMConvertFloatToHalf(xmm0)
    ret

XMConvertFloatToHalf endp

    end
