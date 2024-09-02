; XMVECTORSETINTXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetIntXPtr proc XM_CALLCONV V:FXMVECTOR, p:ptr uint32_t

    ldr rdx,p

    _mm_move_ss(xmm0, [rdx])
    ret

XMVectorSetIntXPtr endp

    end
