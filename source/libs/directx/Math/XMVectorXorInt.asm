; XMVECTORXORINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorXorInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_xor_si128(xmm0, xmm1)
    ret

XMVectorXorInt endp

    end
