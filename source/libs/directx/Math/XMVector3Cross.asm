; XMVECTOR3CROSS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVector3Cross proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    _mm_store_ps(xmm2, XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,2,1)))
    _mm_store_ps(xmm3, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(3,1,0,2)))
    _mm_mul_ps(xmm0, xmm1)
    _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(3,0,2,1))
    _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(3,1,0,2))
    _mm_mul_ps(xmm2, xmm3)
    _mm_sub_ps(xmm0, xmm2)
    _mm_and_ps(xmm0, g_XMMask3)
    ret

XMVector3Cross endp

    end
