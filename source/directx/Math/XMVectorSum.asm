; XMVECTORSUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSum proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSum(xmm0)
    ret

XMVectorSum endp

    end
