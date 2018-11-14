; XMVECTORGREATEROREQUAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGreaterOrEqual proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorGreaterOrEqual(xmm0, xmm1)
    ret

XMVectorGreaterOrEqual endp

    end
