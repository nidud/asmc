; XMVECTORSETINTZ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetIntZ proc XM_CALLCONV V:FXMVECTOR, x:uint32_t

    ldr edx,x
    ;;
    ;; Swap z and x
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    ;;
    ;; Convert input to vector
    ;;
    _mm_cvtsi32_si128(xmm1, edx)
    ;;
    ;; Replace the x component
    ;;
    _mm_move_ss(xmm0, xmm1)
    ;;
    ;; Swap z and x again
    ;;
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    ret

XMVectorSetIntZ endp

    end
