; XMVECTORGETZPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetZPtr proc XM_CALLCONV z:ptr float, V:FXMVECTOR

    ldr rcx,z
    ldr xmm1,V

    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(2,2,2,2))
    _mm_store_ss([rcx], xmm1)
    ret

XMVectorGetZPtr endp

    end
