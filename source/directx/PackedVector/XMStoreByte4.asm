; XMSTOREBYTE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreByte4 proc vectorcall pSource:ptr XMBYTE4, V:FXMVECTOR

    inl_XMStoreByte4(rcx, xmm1)
    ret

XMStoreByte4 endp

    end
