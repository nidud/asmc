; XMVECTORSETXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetXPtr proc XM_CALLCONV V:FXMVECTOR, p:ptr float

    ldr rdx,p

    _mm_move_ss(xmm0, [rdx])
    ret

XMVectorSetXPtr endp

    end
