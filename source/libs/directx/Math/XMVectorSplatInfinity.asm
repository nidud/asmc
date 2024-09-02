; XMVECTORSPLATINFINITY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatInfinity proc XM_CALLCONV

    _mm_store_ps(xmm0, g_XMInfinity)
    ret

XMVectorSplatInfinity endp

    end
