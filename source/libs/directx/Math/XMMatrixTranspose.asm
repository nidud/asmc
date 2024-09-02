; XMMATRIXTRANSPOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixTranspose proc XM_CALLCONV V0:XMVECTOR, V1:XMVECTOR, V2:XMVECTOR, V3:XMVECTOR
ifdef _XM_AVX_INTRINSICS_
    vshufps xmm4,xmm2,xmm3,_MM_SHUFFLE(3,2,3,2)
    vshufps xmm2,xmm2,xmm3,_MM_SHUFFLE(1,0,1,0)
    vshufps xmm3,xmm0,xmm1,_MM_SHUFFLE(3,2,3,2)
    vshufps xmm1,xmm0,xmm1,_MM_SHUFFLE(1,0,1,0)
    vshufps xmm0,xmm1,xmm2,_MM_SHUFFLE(2,0,2,0)
    vshufps xmm1,xmm1,xmm2,_MM_SHUFFLE(3,1,3,1)
    vshufps xmm2,xmm3,xmm4,_MM_SHUFFLE(2,0,2,0)
    vshufps xmm3,xmm3,xmm4,_MM_SHUFFLE(3,1,3,1)
else
    movaps  xmm4,xmm2
    movaps  xmm5,xmm0
    movlhps xmm0,xmm1
    movlhps xmm2,xmm3
    shufps  xmm5,xmm1,_MM_SHUFFLE(3,2,3,2)
    shufps  xmm4,xmm3,_MM_SHUFFLE(3,2,3,2)
    movaps  xmm1,xmm0
    shufps  xmm1,xmm2,_MM_SHUFFLE(3,1,3,1)
    shufps  xmm0,xmm2,_MM_SHUFFLE(2,0,2,0)
    movaps  xmm3,xmm5
    shufps  xmm5,xmm4,_MM_SHUFFLE(2,0,2,0)
    shufps  xmm3,xmm4,_MM_SHUFFLE(3,1,3,1)
    movaps  xmm2,xmm5
endif
    ret

XMMatrixTranspose endp

    end
