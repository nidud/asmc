; XMVECTORTRUNCATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorTruncate proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorTruncate(xmm0)
    ret

XMVectorTruncate endp

    end
