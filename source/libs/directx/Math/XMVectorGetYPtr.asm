; XMVECTORGETYPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetYPtr proc XM_CALLCONV y:ptr float, V:FXMVECTOR

    ldr rcx,y
    ldr xmm1,V

    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(1,1,1,1))
    _mm_store_ss([rcx], xmm1)
    ret

XMVectorGetYPtr endp

    end
