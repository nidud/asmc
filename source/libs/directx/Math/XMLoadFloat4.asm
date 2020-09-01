; XMLOADFLOAT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat4 proc XM_CALLCONV pSource:ptr XMFLOAT4

    .assert( rcx )

    _mm_loadu_ps([rcx])
    ret

XMLoadFloat4 endp

    end
