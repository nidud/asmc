; XMVECTOR3TRANSFORM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVector3Transform proc XM_CALLCONV V:FXMVECTOR, AXMMATRIX

if _XM_VECTORCALL_ eq 0
     _mm_store_ps(xmm0, [rcx])
     _mm_store_ps(xmm1, [rdx+0*16])
     _mm_store_ps(xmm2, [rdx+1*16])
     _mm_store_ps(xmm3, [rdx+2*16])
     _mm_store_ps(xmm4, [rdx+3*16])
endif

    _mm_mul_ps(XM_PERMUTE_PS(_mm_store_ps(xmm5, xmm0), _MM_SHUFFLE(0,0,0,0)), xmm1)
    _mm_mul_ps(XM_PERMUTE_PS(_mm_store_ps(xmm1, xmm0), _MM_SHUFFLE(1,1,1,1)), xmm2)
    _mm_add_ps(xmm5, xmm1)
    _mm_mul_ps(XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(2,2,2,2)), xmm3)
    _mm_add_ps(xmm0, xmm5)
    _mm_add_ps(xmm0, xmm4)

if _XM_VECTORCALL_ eq 0
     _mm_store_ps([rcx], xmm0)
endif
    ret

XMVector3Transform endp

    end
