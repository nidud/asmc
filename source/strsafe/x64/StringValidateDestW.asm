; STRINGVALIDATEDESTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

    option win64:rsp nosave noauto

StringValidateDestW proc pszDest:STRSAFE_PCNZWCH, cchDest:size_t, cchMax:size_t

    mov eax,S_OK

    .if ((!rdx) || (rdx > r8))

        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    ret

StringValidateDestW endp

    end
