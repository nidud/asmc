; XMVECTORSETY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetY proc XM_CALLCONV V:FXMVECTOR, x:float
    ;;
    ;; Swap y and x
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,2,0,1))
    ;;
    ;; Replace the x component
    ;;
    _mm_move_ss(xmm0, xmm1)
    ;;
    ;; Swap y and x again
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,2,0,1))
    ret

XMVectorSetY endp

    end
