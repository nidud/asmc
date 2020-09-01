; XMVECTORSPLATONE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSplatOne proc XM_CALLCONV

    inl_XMVectorSplatOne()
    ret

XMVectorSplatOne endp

    end
