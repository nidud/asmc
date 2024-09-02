; XMVECTORSETINTX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetIntX proc XM_CALLCONV V:FXMVECTOR, x:uint32_t

    ldr edx,x

    _mm_cvtsi32_si128(xmm1, edx)
    _mm_move_ss(xmm0, xmm1)
    ret

XMVectorSetIntX endp

    end
