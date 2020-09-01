; XMSTOREXDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreXDecN4 proc vectorcall pDestination:ptr XMXDECN4, V:FXMVECTOR

    inl_XMStoreXDecN4(rcx, xmm1)
    ret

XMStoreXDecN4 endp

    end
