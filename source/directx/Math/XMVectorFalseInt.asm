; XMVECTORFALSEINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorFalseInt proc XM_CALLCONV

    inl_XMVectorFalseInt()
    ret

XMVectorFalseInt endp

    end
