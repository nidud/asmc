; XMVECTOR_MULTI_SRL_EPI32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVECTOR::multi_srl_epi32 proc vectorcall V:XMVECTOR

    _mm_store_ps(xmm3, xmm0)
    _mm_store_ps(xmm4, xmm1)

    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(0,0,0,0))
    _mm_shuffle_epi32(xmm1, _MM_SHUFFLE(0,0,0,0))
    _mm_and_si128(xmm1, g_XMMaskX)
    _mm_srl_epi32(xmm0, xmm1)

    _mm_store_ps(xmm2, xmm0)    ;; r0

    _mm_store_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm4)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,1,1,1))
    _mm_shuffle_epi32(xmm1, _MM_SHUFFLE(1,1,1,1))
    _mm_and_si128(xmm1, g_XMMaskX)
    _mm_srl_epi32(xmm0, xmm1)

    _mm_store_ps(xmm5, xmm0)    ;; r1

    _mm_store_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm4)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(2,2,2,2))
    _mm_shuffle_epi32(xmm1, _MM_SHUFFLE(2,2,2,2))
    _mm_and_si128(xmm1, g_XMMaskX)
    _mm_srl_epi32(xmm0, xmm1)   ;; r2

    _mm_shuffle_epi32(xmm3, _MM_SHUFFLE(3,3,3,3))
    _mm_shuffle_epi32(xmm4, _MM_SHUFFLE(3,3,3,3))
    _mm_and_si128(xmm4, g_XMMaskX)
    _mm_srl_epi32(xmm3, xmm4)   ;; r3

    ;; (r0,r0,r1,r1)
    _mm_shuffle_ps(xmm2, xmm5, _MM_SHUFFLE(0,0,0,0))
    ;; (r2,r2,r3,r3)
    _mm_shuffle_ps(xmm0, xmm3, _MM_SHUFFLE(0,0,0,0))
    ;; (r0,r1,r2,r3)
    _mm_shuffle_ps(xmm2, xmm0, _MM_SHUFFLE(2,0,2,0))
    _mm_store_ps(xmm0, xmm2)
    ret

XMVECTOR::multi_srl_epi32 endp

    end
