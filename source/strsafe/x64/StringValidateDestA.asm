
include strsafe.inc

    .code

    option win64:rsp nosave noauto

StringValidateDestA proc pszDest:STRSAFE_PCNZCH, cchDest:size_t, cchMax:size_t

    mov eax,S_OK

    .if ((!rdx) || (rdx > r8))

        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    ret

StringValidateDestA endp

    end
