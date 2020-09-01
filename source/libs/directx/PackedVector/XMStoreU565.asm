; XMSTOREU565.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreU565 proc vectorcall pDestination:ptr XMU565, V:FXMVECTOR

    inl_XMStoreU565(rcx, xmm1)
    ret

XMStoreU565 endp

    end
