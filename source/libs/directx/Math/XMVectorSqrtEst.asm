; XMVECTORSQRTEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSqrtEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSqrtEst(xmm0)
    ret

XMVectorSqrtEst endp

    end
