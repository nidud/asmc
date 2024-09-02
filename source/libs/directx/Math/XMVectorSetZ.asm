; XMVECTORSETZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetZ proc XM_CALLCONV V:FXMVECTOR, x:float
    ;;
    ;; Swap z and x
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    ;;
    ;; Replace the x component
    ;;
    _mm_move_ss(xmm0, xmm1)
    ;;
    ;; Swap z and x again
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    ret

XMVectorSetZ endp

    end
