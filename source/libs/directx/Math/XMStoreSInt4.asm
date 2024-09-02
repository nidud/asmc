; XMSTORESINT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreSInt4 proc XM_CALLCONV pDestination:ptr XMINT4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_store_ps(xmm0, g_XMMaxInt)
    _mm_store_ps(xmm2, g_XMAbsMask)
    _mm_cmpgt_ps(xmm0, xmm1, xmm0)
    _mm_cvttps_epi32(xmm1)
    _mm_and_ps(xmm2, xmm0)
    _mm_andnot_ps(xmm0, xmm1)
    _mm_or_ps(xmm0, xmm2)
    _mm_storeu_si128([rcx], xmm0)
    ret

XMStoreSInt4 endp

    end
