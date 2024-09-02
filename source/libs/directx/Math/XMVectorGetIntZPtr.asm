; XMVECTORGETINTZPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetIntZPtr proc XM_CALLCONV p:ptr uint32_t, V:FXMVECTOR

    ldr rcx,p
    ldr xmm1,V

    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(2,2,2,2))
    _mm_store_ss([rcx], xmm1)
    ret

XMVectorGetIntZPtr endp

    end
