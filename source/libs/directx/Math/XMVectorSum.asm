; XMVECTORSUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSum proc XM_CALLCONV V:FXMVECTOR
ifdef _XM_SSE3_INTRINSICS_
    _mm_hadd_ps(xmm0, xmm0)
    _mm_hadd_ps(xmm0, xmm0)
else
    _mm_store_ps(xmm1, xmm0)
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(2, 3, 0, 1))
    _mm_add_ps(xmm0, xmm1)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(1, 0, 3, 2))
    _mm_add_ps(xmm0, xmm0)
endif
    ret

XMVectorSum endp

    end
