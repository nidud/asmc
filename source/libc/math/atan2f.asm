; ATAN2F.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
ifdef _WIN64
include intrin.inc
undef __vdecl_atan2f4
alias <__vdecl_atan2f4>=<atan2f>
assume uses xmm6 xmm7
endif

.code

atan2f proc y:float, x:float
ifdef _WIN64

  local Pi:     XVECTOR,
        Pi_2:   XVECTOR,
        Pi_4:   XVECTOR,
        Pi3_4:  XVECTOR

    _mm_store_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, xmm1)
    _mm_store_ps(xmm5, _mm_atan_ps(_mm_div_ps(xmm0, xmm1)))
    _mm_store_ps(xmm1, g_X4FNEGZERO)
    _mm_and_ps(_mm_store_ps(xmm4, xmm7), xmm1)
    _mm_cmpeq_epi32(xmm4, g_X4FZERO)
    _mm_store_ps(xmm2, xmm6)
    _mm_and_ps(xmm2, g_X4FNEGZERO)
    _mm_store_ps(xmm0, xmm2)
    _mm_or_si128(xmm0, g_X4FPI)
    _mm_store_ps(Pi, xmm0)
    _mm_store_ps(xmm0, g_X4FPI_2)
    _mm_or_si128(xmm0, xmm2)
    _mm_store_ps(Pi_2, xmm0)
    _mm_store_ps(xmm0, { M_PI_4, M_PI_4, M_PI_4, M_PI_4 })
    _mm_or_si128(xmm0, xmm2)
    _mm_store_ps(Pi_4, xmm0)
    _mm_store_ps(xmm0, { M_PI * 3.0 / 4.0, M_PI * 3.0 / 4.0, M_PI * 3.0 / 4.0, M_PI * 3.0 / 4.0 })
    _mm_or_si128(xmm0, xmm2)
    _mm_store_ps(Pi3_4, xmm0)
    _mm_store_ps(xmm1, xmm7)
    _mm_and_ps(xmm1, g_X4IABSMASK)
    _mm_cmpeq_ps(xmm1, g_X4IINFINITY)
    _mm_store_ps(xmm0, xmm4)
    _mm_and_ps(xmm2, xmm0)
    _mm_andnot_ps(xmm0, Pi)
    _mm_or_ps(xmm0, xmm2)
    _mm_cmpeq_ps(xmm7, g_X4FZERO)
    _mm_store_ps(xmm2, Pi_2)
    _mm_and_ps(xmm2, xmm7)
    _mm_cmpeq_ps(xmm3, xmm3)
    _mm_andnot_ps(xmm7, xmm3)
    _mm_or_ps(xmm7, xmm2)
    _mm_store_ps(xmm2, xmm6)
    _mm_and_ps(xmm2, g_X4IABSMASK)
    _mm_cmpeq_ps(xmm2, g_X4IINFINITY)
    _mm_cmpeq_ps(xmm6, g_X4FZERO)
    _mm_and_ps(xmm0, xmm6)
    _mm_andnot_ps(xmm6, xmm7)
    _mm_or_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, xmm6)
    _mm_store_ps(xmm0, Pi_4)
    _mm_store_ps(xmm6, xmm4)
    _mm_and_ps(xmm0, xmm6)
    _mm_andnot_ps(xmm6, Pi3_4)
    _mm_or_ps(xmm6, xmm0)
    _mm_and_ps(xmm6, xmm1)
    _mm_andnot_ps(xmm1, Pi_2)
    _mm_or_ps(xmm1, xmm6)
    _mm_and_ps(xmm1, xmm2)
    _mm_andnot_ps(xmm2, xmm7)
    _mm_or_ps(xmm2, xmm1)
    _mm_cmpeq_epi32(xmm3, xmm2)
    _mm_store_ps(xmm1, g_X4FNEGZERO)
    _mm_and_ps(xmm1, xmm4)
    _mm_andnot_ps(xmm4, Pi)
    _mm_or_ps(xmm4, xmm1)
    _mm_add_ps(xmm5, xmm4)
    _mm_and_ps(xmm5, xmm3)
    _mm_andnot_ps(xmm3, xmm2)
    _mm_or_ps(xmm3, xmm5)
    _mm_store_ps(xmm0, xmm3)
else
    fld y
    fld x
    fpatan
endif
    ret
    endp

    end
