; XMVECTORGETINTWPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntWPtr proc XM_CALLCONV x:ptr uint32_t, V:FXMVECTOR

    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(3,3,3,3))
    movaps [rcx],xmm1
    ret

XMVectorGetIntWPtr endp

    end
