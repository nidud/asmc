; XMLOADFLOAT2A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat2A proc XM_CALLCONV pSource:ptr XMFLOAT2A

    .assert( rcx )

    _mm_loadl_epi64(rcx)
    ret

XMLoadFloat2A endp

    end
