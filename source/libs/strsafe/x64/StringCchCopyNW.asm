; STRINGCCHCOPYNW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCopyNW proc frame pszDest:STRSAFE_LPWSTR,
        cchDest:size_t, pszSrc:STRSAFE_PCNZWCH, cchToCopy:size_t

    StringValidateDestW(rcx, rdx, STRSAFE_MAX_CCH)

    mov rcx,pszDest
    mov rdx,cchDest

    .ifs (SUCCEEDED(eax))

        .if (cchToCopy > STRSAFE_MAX_LENGTH)

            mov eax,STRSAFE_E_INVALID_PARAMETER
            mov word ptr [rcx],0
        .else

            StringCopyWorkerW(rcx, rdx, NULL, pszSrc, cchToCopy)
        .endif
    .elseif rdx

        mov word ptr [rcx],0
    .endif
    ret

StringCchCopyNW endp

    end
