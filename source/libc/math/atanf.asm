; ATANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_atanf4
alias <__vdecl_atanf4>=<atanf>
define g_X4FATANCOEFFICIENTS0 <{ -0.3333314528, +0.1999355085, -0.1420889944, +0.1065626393 }>
define g_X4FATANCOEFFICIENTS1 <{ -0.0752896400, +0.0429096138, -0.0161657367, +0.0028662257 }>
endif

.code

atanf proc x:float
ifdef _WIN64

    _mm_store_ps(xmm3, g_X4FONE)
    _mm_cmpgt_ps(xmm2, xmm0, xmm3)
    _mm_store_ps(xmm1, xmm2)
    _mm_and_ps(xmm1, xmm3)
    _mm_andnot_ps(xmm2, g_X4FNEGONE)
    _mm_or_ps(xmm2, xmm1)
    _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(xmm5), xmm0), xmm0)
    _mm_cmple_ps(xmm5, xmm3)
    _mm_store_ps(xmm1, xmm5)
    _mm_store_ps(xmm4, xmm5)
    _mm_andnot_ps(xmm5, xmm2)
    _mm_and_ps(xmm1, xmm0)
    _mm_andnot_ps(xmm4, _mm_div_ps(xmm3, xmm0))
    _mm_or_ps(xmm1, xmm4)
    _mm_mul_ps(_mm_store_ps(xmm0, xmm1), xmm0)

    _mm_store_ps(xmm3, _mm_store_ps(xmm2, g_X4FATANCOEFFICIENTS1))
    _mm_mul_ps(_mm_permute_ps(xmm2, _MM_SHUFFLE(3, 3, 3, 3)), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm3, _MM_SHUFFLE(0, 0, 0, 0))), xmm0)
    _mm_store_ps(xmm3, g_X4FATANCOEFFICIENTS0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(3, 3, 3, 3))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(2, 2, 2, 2))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(_mm_store_ps(xmm4, xmm3), _MM_SHUFFLE(1, 1, 1, 1))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, _mm_permute_ps(xmm3, _MM_SHUFFLE(0, 0, 0, 0))), xmm0)
    _mm_mul_ps(_mm_add_ps(xmm2, g_X4FONE), xmm1)
    _mm_store_ps(xmm0, xmm5)
    _mm_sub_ps(_mm_mul_ps(xmm5, g_X4FPI_2), xmm2)

    _mm_cmpeq_ps(xmm0, _mm_setzero_ps(xmm3))
    _mm_store_ps(xmm3, xmm0)
    _mm_and_ps(xmm0, xmm2)
    _mm_andnot_ps(xmm3, xmm5)
    _mm_or_ps(xmm0, xmm3)
else
    fld x
    fld1
    fpatan
endif
    ret
    endp

    end
