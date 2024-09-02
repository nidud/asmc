; XMVECTORFALSEINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorFalseInt proc XM_CALLCONV

    _mm_setzero_ps()
    ret

XMVectorFalseInt endp

    end
