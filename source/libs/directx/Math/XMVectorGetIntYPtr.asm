; XMVECTORGETINTYPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetIntYPtr proc XM_CALLCONV p:ptr uint32_t, V:FXMVECTOR

    ldr rcx,p
    ldr xmm1,V

    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(1,1,1,1))
    _mm_store_ss([rcx], xmm1)
    ret

XMVectorGetIntYPtr endp

    end
