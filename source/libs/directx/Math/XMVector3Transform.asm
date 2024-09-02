; XMVECTOR3TRANSFORM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVector3Transform proc XM_CALLCONV V:FXMVECTOR, V0:XMVECTOR, V1:XMVECTOR, V2:XMVECTOR, V3:XMVECTOR

    _mm_mul_ps(XM_PERMUTE_PS(_mm_store_ps(xmm5, xmm0), _MM_SHUFFLE(0,0,0,0)), xmm1)
    _mm_mul_ps(XM_PERMUTE_PS(_mm_store_ps(xmm1, xmm0), _MM_SHUFFLE(1,1,1,1)), xmm2)
    _mm_add_ps(xmm5, xmm1)
    _mm_mul_ps(XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(2,2,2,2)), xmm3)
    _mm_add_ps(xmm0, xmm5)
    _mm_add_ps(xmm0, xmm4)
    ret

XMVector3Transform endp

    end
