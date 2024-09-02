; XMVECTORSETW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetW proc XM_CALLCONV V:FXMVECTOR, x:float
    ;;
    ;; Swap w and x
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0,2,1,3))
    ;;
    ;; Replace the x component
    ;;
    _mm_move_ss(xmm0, xmm1)
    ;;
    ;; Swap w and x again
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0,2,1,3))
    ret

XMVectorSetW endp

    end
