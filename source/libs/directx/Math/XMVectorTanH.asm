; XMVECTORTANH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .data
    ;;
    ;; 2.0f / ln(2.0f)
    ;;
    Scale XMVECTORF32 { { { 2.8853900817779268, 2.8853900817779268, 2.8853900817779268, 2.8853900817779268 } } }

    .code

XMVectorTanH proc XM_CALLCONV V:FXMVECTOR

    XMVectorExp(_mm_mul_ps(xmm0, Scale))
    _mm_mul_ps(xmm0, g_XMOneHalf.v)
    _mm_add_ps(xmm0, g_XMOneHalf.v)
    _mm_store_ps(xmm1, g_XMOne.v)
    _mm_store_ps(xmm2, xmm1)
    _mm_div_ps(xmm1, xmm0)
    _mm_sub_ps(xmm2, xmm1)
    _mm_store_ps(xmm0, xmm2)
    ret

XMVectorTanH endp

    end
