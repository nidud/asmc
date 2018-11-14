; XMVECTORMULTIPLYADD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorMultiplyAdd proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, V3:FXMVECTOR

    inl_XMVectorMultiplyAdd(xmm0, xmm1, xmm2)
    ret

XMVectorMultiplyAdd endp

    end
