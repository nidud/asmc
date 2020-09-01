; XMSTOREXDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreXDec4 proc vectorcall pDestination:ptr XMXDEC4, V:FXMVECTOR

    inl_XMStoreXDec4(rcx, xmm1)
    ret

XMStoreXDec4 endp

    end
