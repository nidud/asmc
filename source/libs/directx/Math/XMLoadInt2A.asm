; XMLOADINT2A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadInt2A proc XM_CALLCONV pSource:ptr uint32_t

    .assert( rcx )
    .assert( !(ecx & 0xF) )

    _mm_loadl_epi64(rcx)
    ret

XMLoadInt2A endp

    end
