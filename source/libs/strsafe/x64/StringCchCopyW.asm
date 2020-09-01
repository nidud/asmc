; STRINGCCHCOPYW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCopyW proc pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR

    StringValidateDestW(rcx, rdx, STRSAFE_MAX_CCH)

    mov rcx,pszDest
    mov rdx,cchDest

    .ifs (SUCCEEDED(eax))

        StringCopyWorkerW(rcx,
                rdx,
                NULL,
                pszSrc,
                STRSAFE_MAX_LENGTH)

    .elseif rdx

        mov word ptr [rcx],0
    .endif
    ret

StringCchCopyW endp

    end
