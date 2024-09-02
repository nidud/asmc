; XMVECTORSIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSin proc XM_CALLCONV V:FXMVECTOR
    ;;
    ;; Force the value within the bounds of pi
    ;;
    XMVectorModAngles(xmm0)
    _mm_store_ps(xmm1, xmm0)
    ;;
    ;; Map in [-pi/2,pi/2] with sin(y) = sin(x).
    ;;
    _mm_and_ps(xmm1, g_XMNegativeZero)
    _mm_store_ps(xmm2, xmm1)
    _mm_or_ps(xmm2, g_XMPi) ; pi when x >= 0, -pi when x < 0
    _mm_store_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm3, xmm0)   ; |x|
    _mm_sub_ps(xmm2, xmm0)
    _mm_cmple_ps(xmm3, g_XMHalfPi)
    _mm_and_ps(xmm0, xmm3)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_or_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm1, xmm0)
    ;;
    ;; Compute polynomial approximation
    ;;
    _mm_store_ps(xmm3, g_XMSinCoefficients1)
    _mm_store_ps(xmm2, XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm3, g_XMSinCoefficients0)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, XM_PERMUTE_PS(xmm4, _MM_SHUFFLE(3,3,3,3)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, XM_PERMUTE_PS(xmm4, _MM_SHUFFLE(2,2,2,2)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm4, xmm3)
    _mm_add_ps(xmm2, XM_PERMUTE_PS(xmm4, _MM_SHUFFLE(1,1,1,1)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_add_ps(xmm2, g_XMOne)
    _mm_mul_ps(xmm0, xmm2)
    ret

XMVectorSin endp

    end
