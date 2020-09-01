; XMVECTORCEILING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorCeiling proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorCeiling(xmm0)
    ret

XMVectorCeiling endp

    end
