; XMLOADFLOAT4A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadFloat4A proc XM_CALLCONV pSource:ptr XMFLOAT4A

    ldr rcx,pSource

    _mm_load_ps([rcx])
    ret

XMLoadFloat4A endp

    end
