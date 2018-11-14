; XMSTORECOLOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreColor proc vectorcall pSource:ptr XMCOLOR, V:FXMVECTOR

    inl_XMStoreColor(rcx, xmm1)
    ret

XMStoreColor endp

    end
