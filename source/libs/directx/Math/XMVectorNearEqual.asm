; XMVECTORNEAREQUAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorNearEqual proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, Epsilon:FXMVECTOR
    ;;
    ;; Get the difference
    ;;
    _mm_sub_ps(xmm0, xmm1)
    ;;
    ;; Get the absolute value of the difference
    ;;
    _mm_setzero_ps(xmm3)
    _mm_sub_ps(xmm3, xmm0)
    _mm_max_ps(xmm0, xmm3)
    _mm_cmple_ps(xmm0, xmm2)
    ret

XMVectorNearEqual endp

    end
