; XMLOADFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadFloat proc XM_CALLCONV pSource:ptr float

    ldr rcx,pSource

    _mm_load_ss([rcx])
    ret

XMLoadFloat endp

    end
