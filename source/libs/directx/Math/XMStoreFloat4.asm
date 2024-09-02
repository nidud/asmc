; XMSTOREFLOAT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMStoreFloat4 proc XM_CALLCONV pDestination:ptr XMFLOAT4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm1,V

    _mm_storeu_ps([rcx], xmm1)
    ret

XMStoreFloat4 endp

    end
