; XMVECTORINBOUNDS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorInBounds proc XM_CALLCONV V:FXMVECTOR, Bounds:FXMVECTOR

    _mm_store_ps(xmm2, xmm0)
    ;;
    ;; Test if less than or equal
    ;;
    _mm_cmple_ps(xmm0, xmm1)
    ;;
    ;; Negate the bounds
    ;;
    _mm_mul_ps(xmm1, g_XMNegativeOne)
    ;;
    ;; Test if greater or equal (Reversed)
    ;;
    _mm_cmple_ps(xmm1, xmm2)
    _mm_and_ps(xmm0, xmm1)
    ret

XMVectorInBounds endp

    end
