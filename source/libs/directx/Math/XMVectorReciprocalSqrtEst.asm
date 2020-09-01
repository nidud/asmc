; XMVECTORRECIPROCALSQRTEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReciprocalSqrtEst proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorReciprocalSqrtEst(xmm0)
    ret

XMVectorReciprocalSqrtEst endp

    end
