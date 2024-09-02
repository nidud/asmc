; XMVECTORCOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorCos proc XM_CALLCONV V:FXMVECTOR
    ;;
    ;; Map V to x in [-pi,pi].
    ;;
    XMVectorModAngles(xmm0)         ;; x
    _mm_store_ps(xmm1, xmm0)        ;; sign
    _mm_and_ps(xmm1, g_XMNegativeZero)
    _mm_store_ps(xmm2, xmm1)
    _mm_or_ps(xmm2, g_XMPi)         ;; pi when x >= 0, -pi when x < 0
    _mm_store_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm3, xmm0)       ;; absx
    _mm_sub_ps(xmm2, xmm0)          ;; rflx
    _mm_cmple_ps(xmm3, g_XMHalfPi)  ;; comp
    _mm_store_ps(xmm4, xmm3)
    _mm_and_ps(xmm0, xmm3)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_or_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm0)
    _mm_mul_ps(xmm1, xmm0)          ;; x2
    _mm_store_ps(xmm0, xmm4)        ;; sign
    _mm_and_ps(xmm0, g_XMOne)
    _mm_andnot_ps(xmm4, g_XMNegativeOne)
    _mm_or_ps(xmm0, xmm4)
    ;;
    ;; Compute polynomial approximation
    ;;
    _mm_store_ps(xmm3, g_XMCosCoefficients1)
    _mm_store_ps(xmm2, XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(0,0,0,0)))
    _mm_mul_ps(xmm2, xmm1)
    _mm_store_ps(xmm3, g_XMCosCoefficients0)
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

XMVectorCos endp

    end
