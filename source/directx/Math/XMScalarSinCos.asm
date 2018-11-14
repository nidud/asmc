; XMSCALARSINCOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMScalarSinCos proc XM_CALLCONV pSin:ptr float, pCos:ptr float, Value:float

    inl_XMScalarSinCos(xmm2)
    movss [rcx],xmm0
    movss [rdx],xmm1
    ret

XMScalarSinCos endp

    end
