; XMVECTORMODANGLES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorModAngles proc XM_CALLCONV V:FXMVECTOR

    _mm_store_ps(xmm5, xmm0)
    ;;
    ;; Modulo the range of the given angles such that -XM_PI <= Angles < XM_PI
    ;;
    _mm_mul_ps(xmm0, g_XMReciprocalTwoPi)
    ;;
    ;; Use the inline function due to complexity for rounding
    ;;
    XMVectorRound(xmm0)
    _mm_mul_ps(xmm0, g_XMTwoPi)
    _mm_sub_ps(xmm5, xmm0)
    _mm_store_ps(xmm0, xmm5)
    ret

XMVectorModAngles endp

    end
