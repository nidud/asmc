; XMVECTORRECIPROCALSQRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReciprocalSqrt proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorReciprocalSqrt(xmm0)
    ret

XMVectorReciprocalSqrt endp

    end
