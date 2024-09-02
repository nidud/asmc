; XMVECTORSETZPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetZPtr proc XM_CALLCONV V:FXMVECTOR, p:ptr float

    ldr rdx,p

    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    ;;
    ;; Replace the x component
    ;;
    _mm_move_ss(xmm0, [rdx])
    ;;
    ;; Swap z and x again
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    ret

XMVectorSetZPtr endp

    end
