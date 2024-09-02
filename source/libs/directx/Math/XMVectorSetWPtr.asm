; XMVECTORSETWPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetWPtr proc XM_CALLCONV V:FXMVECTOR, p:ptr float

    ldr rdx,p
    ;;
    ;; Swap w and x
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0,2,1,3))
    ;;
    ;; Replace the x component
    ;;
    _mm_move_ss(xmm0, [rdx])
    ;;
    ;; Swap w and x again
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0,2,1,3))
    ret

XMVectorSetWPtr endp

    end
