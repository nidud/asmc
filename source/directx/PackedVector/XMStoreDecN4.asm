; XMSTOREDECN4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreDecN4 proc vectorcall pSource:ptr XMDECN4, V:FXMVECTOR

    inl_XMStoreDecN4(rcx, xmm1)
    ret

XMStoreDecN4 endp

    end
