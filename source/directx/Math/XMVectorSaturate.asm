; XMVECTORSATURATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSaturate proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSaturate(xmm0)
    ret

XMVectorSaturate endp

    end
