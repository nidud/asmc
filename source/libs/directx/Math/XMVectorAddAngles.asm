; XMVECTORADDANGLES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorAddAngles proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR
    ;;
    ;; Adjust the angles
    ;;
    _mm_add_ps(xmm0, xmm1)
    _mm_store_ps(xmm1, xmm0)
    _mm_cmplt_ps(xmm1, g_XMNegativePi)
    ;;
    ;; Less than Pi?
    ;;
    _mm_and_ps(xmm1, g_XMTwoPi)
    ;;
    ;; Add 2Pi to all entries less than -Pi
    ;;
    _mm_add_ps(xmm0, xmm1)
    ;;
    ;; Greater than or equal to Pi?
    ;;
    _mm_store_ps(xmm1, g_XMPi)
    _mm_cmple_ps(xmm1, xmm0)
    _mm_and_ps(xmm1, g_XMTwoPi)
    ;;
    ;; Sub 2Pi to all entries greater than Pi
    ;;
    _mm_sub_ps(xmm0, xmm1)
    ret

XMVectorAddAngles endp

    end
