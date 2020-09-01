; XMVECTORSPLATEPSILON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSplatEpsilon proc XM_CALLCONV

    inl_XMVectorSplatEpsilon()
    ret

XMVectorSplatEpsilon endp

    end
