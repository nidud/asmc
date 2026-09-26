; TANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc

undef __vdecl_tanf4
alias <__vdecl_tanf4>=<tanf>

define g_X4FTANCONSTANTS        <{ 1.570796371, 6.077100628e-11, 0.000244140625, 0.63661977228 }>
define g_X4FTANCOEFFICIENTS0    <{ 1.0, -4.667168334e-1, 2.566383229e-2, -3.118153191e-4 }>
define g_X4FTANCOEFFICIENTS1    <{ 4.981943399e-7, -1.333835001e-1, 3.424887824e-3, -1.786170734e-5 }>
endif

.code

tanf proc x:float

ifdef _WIN64

   .new V0:real16 = xmm0
   .new V6:real16 = xmm6
   .new V7:real16 = xmm7

    _mm_store_ps(xmm7, xmm0)
    _mm_store_ps(xmm4, _mm_store_ps(xmm1, g_X4FTANCONSTANTS))
    _mm_mul_ps(xmm0, _mm_shuffle_ps(xmm1, xmm1, _MM_SHUFFLE(3, 3, 3, 3)))
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    _mm_store_ps(xmm1, xmm4)
    _mm_sub_ps(xmm7, _mm_mul_ps(_mm_shuffle_ps(xmm1, xmm1, _MM_SHUFFLE(0, 0, 0, 0)), xmm0))
    _mm_sub_ps(_mm_setzero_ps(xmm1), xmm0)
    _mm_store_ps(xmm6, xmm0)
    _mm_max_ps(xmm6, xmm1)
    _mm_cvttps_epi32(xmm6)
    _mm_sub_ps(xmm7, _mm_mul_ps(_mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(1, 1, 1, 1)), xmm0))
    _mm_mul_ps(_mm_store_ps(xmm0, xmm7), xmm0)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm3, _mm_store_ps(xmm2, g_X4FTANCOEFFICIENTS1))
    _mm_store_ps(xmm4, xmm2)
    _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(3, 3, 3, 3))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm2), _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(2, 2, 2, 2)))
    _mm_store_ps(xmm3, _mm_store_ps(xmm2, g_X4FTANCOEFFICIENTS0))
    _mm_shuffle_ps(_mm_store_ps(xmm5, xmm4), xmm5, _MM_SHUFFLE(0, 0, 0, 0))
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(3, 3, 3, 3)))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm1), _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(1, 1, 1, 1)))
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(2, 2, 2, 2)))
    _mm_mul_ps(xmm0, xmm1)
    _mm_store_ps(xmm3, _mm_store_ps(xmm2, g_X4FTANCOEFFICIENTS0))
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(1, 1, 1, 1)))
    _mm_add_ps(_mm_mul_ps(xmm0, xmm7), xmm7)
    _mm_store_ps(xmm4, xmm7)
    _mm_cmple_ps(xmm4, _mm_shuffle_ps(_mm_store_ps(xmm2, g_X4FTANCONSTANTS), xmm2, _MM_SHUFFLE(2, 2, 2, 2)))
    _mm_mul_ps(xmm2, { -1.0, -1.0, -1.0, -1.0 })
    _mm_cmple_ps(xmm2, xmm7)
    _mm_and_ps(xmm4, xmm2)
    _mm_add_ps(_mm_mul_ps(xmm5, xmm1), _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(0, 0, 0, 0)))
    _mm_store_ps(xmm2, xmm4)
    _mm_and_ps(xmm7, xmm2)
    _mm_andnot_ps(xmm2, xmm0)
    _mm_or_ps(xmm2, xmm7)
    _mm_store_ps(xmm3, { 1.0, 1.0, 1.0, 1.0 })
    _mm_and_ps(xmm3, xmm4)
    _mm_andnot_ps(xmm4, xmm5)
    _mm_or_ps(xmm4, xmm3)
    _mm_sub_ps(_mm_setzero_ps(), xmm2)
    _mm_div_ps(xmm2, xmm4)
    _mm_div_ps(xmm4, xmm0)
    _mm_and_ps(xmm6, { 1, 1, 1, 1 })
    _mm_cmpeq_epi32(xmm6, _mm_setzero_ps())
    _mm_cmpeq_ps(xmm0, V0)
    _mm_and_ps(xmm2, xmm6)
    _mm_andnot_ps(xmm6, xmm4)
    _mm_or_ps(xmm6, xmm2)
    _mm_andnot_ps(xmm0, xmm6)
    _mm_store_ps(xmm6, V6)
    _mm_store_ps(xmm7, V7)
else
    fld x
    fptan
    fstp st(0)
endif
    ret
    endp

    end
