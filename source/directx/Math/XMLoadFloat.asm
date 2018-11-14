; XMLOADFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat proc XM_CALLCONV pSource:ptr float

    .assert( rcx )
    .assert( !( ecx & 0xF) )

    _mm_load_ss([rcx])
    ret

XMLoadFloat endp

    end
