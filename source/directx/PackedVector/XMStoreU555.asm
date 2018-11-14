; XMSTOREU555.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreU555 proc vectorcall pDestination:ptr XMU555, V:FXMVECTOR

    inl_XMStoreU555(rcx, xmm1)
    ret

XMStoreU555 endp

    end
