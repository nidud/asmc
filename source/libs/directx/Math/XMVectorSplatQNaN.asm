; XMVECTORSPLATQNAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatQNaN proc XM_CALLCONV

    _mm_store_ps(xmm0, g_XMQNaN)
    ret

XMVectorSplatQNaN endp

    end
