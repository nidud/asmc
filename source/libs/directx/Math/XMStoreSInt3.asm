; XMSTORESINT3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreSInt3 proc XM_CALLCONV pDestination:ptr XMINT3, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    _mm_store_ps(xmm1, g_XMMaxInt)
    _mm_store_ps(xmm3, g_XMAbsMask)
    ;;
    ;; Float to int conversion
    ;;
    _mm_cvttps_epi32(xmm2, xmm0)
    _mm_cmplt_ps(xmm1, xmm0)
    _mm_and_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm1, xmm2)
    _mm_store_ps(xmm0, xmm1)
    _mm_or_ps(xmm0, xmm3)
    _mm_store_ps(xmm2, xmm0)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ss([rcx][0], xmm0)
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(1, 1, 1, 1))
    _mm_shuffle_ps(xmm2, xmm0, _MM_SHUFFLE(2, 2, 2, 2))
    _mm_store_ss([rcx][4], xmm1)
    _mm_store_ss([rcx][8], xmm2)
    ret

XMStoreSInt3 endp

    end
