; XMVECTORSETINTX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntX proc XM_CALLCONV V:FXMVECTOR, x:uint32_t

    inl_XMVectorSetIntX(xmm0, edx)
    ret

XMVectorSetIntX endp

    end
