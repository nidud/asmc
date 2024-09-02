; XMVECTORNORINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorNorInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_or_si128(xmm0, xmm1)
    _mm_andnot_si128(xmm0, g_XMNegOneMask)
    ret

XMVectorNorInt endp

    end
