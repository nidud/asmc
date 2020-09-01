; XMVECTORSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSet proc XM_CALLCONV C0:float, C1:float, C2:float, C3:float

    unpcklps xmm0,xmm1
    unpcklps xmm2,xmm3
    movlhps  xmm0,xmm2
    ret

XMVectorSet endp

    end
