; XMSTORESINT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreSInt2 proc XM_CALLCONV pDestination:ptr XMINT2, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    _mm_store_ps(xmm1, g_XMMaxInt)
    _mm_store_ps(xmm3, g_XMAbsMask)
    ;;
    ;; Float to int conversion
    ;;
    _mm_cvttps_epi32(xmm2, xmm0)
    ;;
    ;; In case of positive overflow, detect it
    ;;
    _mm_cmpgt_ps(xmm1, xmm0, xmm1)
    ;;
    ;; If there was positive overflow, set to 0x7FFFFFFF
    ;;
    _mm_and_ps(xmm3, xmm1)
    _mm_andnot_ps(xmm1, xmm2)
    _mm_or_ps(xmm1, xmm3)
    ;;
    ;; Write two ints
    ;;
    _mm_store_ss([rcx][0], xmm1)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(1, 1, 1, 1))
    _mm_store_ss([rcx][4], xmm1)
    ret

XMStoreSInt2 endp

    end
