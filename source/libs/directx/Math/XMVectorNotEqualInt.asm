; XMVECTORNOTEQUALINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorNotEqualInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_cmpeq_epi32(xmm0, xmm1)
    _mm_xor_ps(xmm0, g_XMNegOneMask)
    ret

XMVectorNotEqualInt endp

    end
