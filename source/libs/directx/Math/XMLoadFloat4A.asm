; XMLOADFLOAT4A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat4A proc XM_CALLCONV pSource:ptr XMFLOAT4A

    .assert( rcx )

    _mm_load_ps([rcx])
    ret

XMLoadFloat4A endp

    end
