; XMSTOREUINT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreUInt2 proc XM_CALLCONV pDestination:ptr XMUINT2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    _mm_max_ps(xmm0, g_XMZero)
    _mm_store_ps(xmm2, g_XMUnsignedFix)
    _mm_store_ps(xmm3, g_XMMaxUInt)
    _mm_store_ps(xmm1, xmm2)
    _mm_cmple_ps(xmm1, xmm0)
    _mm_cmplt_ps(xmm3, xmm0)
    _mm_and_ps(xmm2, xmm1)
    _mm_and_ps(xmm1, g_XMNegativeZero)
    _mm_sub_ps(xmm0, xmm2)
    _mm_cvttps_epi32(xmm0, xmm0)
    _mm_xor_ps(xmm0, xmm1)
    _mm_or_ps(xmm0, xmm3)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ss([rcx][0], xmm0)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(1, 1, 1, 1))
    _mm_store_ss([rcx][4], xmm1)
    ret

XMStoreUInt2 endp

    end
