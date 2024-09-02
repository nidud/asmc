; XMVECTORSETYPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetYPtr proc XM_CALLCONV V:FXMVECTOR, p:ptr float

    ldr rdx,p

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,2,0,1))
    ;;
    ;; Replace the x component
    ;;
    _mm_move_ss(xmm0, [rdx])
    ;;
    ;; Swap y and x again
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,2,0,1))
    ret

XMVectorSetYPtr endp

    end
