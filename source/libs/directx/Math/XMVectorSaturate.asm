; XMVECTORSATURATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSaturate proc XM_CALLCONV V:FXMVECTOR
    ;;
    ;; Set <0 to 0
    ;;
    _mm_max_ps(xmm0, g_XMZero)
    ;;
    ;; Set>1 to 1
    ;;
    _mm_min_ps(xmm0, g_XMOne)
    ret

XMVectorSaturate endp

    end
