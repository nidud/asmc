; XMVECTORCOSEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorCosEst proc XM_CALLCONV V:FXMVECTOR
    ;;
    ;; Map V to x in [-pi,pi].
    ;;
    XMVectorModAngles(xmm0)
    ;;
    ;; Map in [-pi/2,pi/2] with cos(y) = sign*cos(x).
    ;;
    _mm_and_ps(_mm_store_ps(xmm1, xmm0), g_XMNegativeZero)
    ;;
    ;; pi when x >= 0, -pi when x < 0
    ;;
    _mm_or_ps(_mm_store_ps(xmm2, g_XMPi), xmm1)
    ;;
    ;; |x|
    ;;
    _mm_andnot_ps(xmm1, xmm0)
    _mm_sub_ps(xmm2, xmm0)
    _mm_cmple_ps(xmm1, g_XMHalfPi)
    _mm_store_ps(xmm4, xmm1)
    _mm_store_ps(xmm3, xmm1)

    _mm_and_ps(xmm3, xmm0)
    _mm_andnot_ps(xmm1, xmm2)
    _mm_or_ps(xmm1, xmm3)
    _mm_mul_ps(xmm1, xmm1)

    _mm_and_ps(_mm_store_ps(xmm2, xmm4), g_XMOne)
    _mm_andnot_ps(xmm4, g_XMNegativeOne)
    _mm_or_ps(xmm4, xmm2)
    ;;
    ;; Compute polynomial approximation
    ;;
    _mm_store_ps(xmm0, g_XMCosCoefficients1)
    _mm_store_ps(xmm2, xmm0)
    _mm_store_ps(xmm3, xmm0)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,3,3,3))
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(2,2,2,2)))
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(1,1,1,1)))
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, g_XMOne)
    _mm_mul_ps(xmm0, xmm4)
    ret

XMVectorCosEst endp

    end
