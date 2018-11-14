; XMSTOREDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreDec4 proc vectorcall pSource:ptr XMDEC4, V:FXMVECTOR

    inl_XMStoreDec4(rcx, xmm1)
    ret

XMStoreDec4 endp

    end
