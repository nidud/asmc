; STRINGVALIDATEDESTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringValidateDestA proc WINAPI pszDest:STRSAFE_PCNZCH, cchDest:size_t, cchMax:size_t

    mov eax,S_OK
    mov edx,cchDest

    .if (!edx || edx > cchMax)

        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    ret

StringValidateDestA endp

    end
