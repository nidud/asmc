; XMSTOREBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreByte2 proc vectorcall pSource:ptr XMBYTE2, V:FXMVECTOR

    inl_XMStoreByte2(rcx, xmm1)
    ret

XMStoreByte2 endp

    end
