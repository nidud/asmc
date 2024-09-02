; XMVECTORISINFINITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorIsInfinite proc XM_CALLCONV V:FXMVECTOR
    ;;
    ;; Mask off the sign bit
    ;;
    _mm_and_ps(xmm0, g_XMAbsMask)
    ;;
    ;; Compare to infinity
    ;;
    _mm_cmpeq_ps(xmm0, g_XMInfinity)
    ;;
    ;; If any are infinity, the signs are true.
    ;;
    ret

XMVectorIsInfinite endp

    end
