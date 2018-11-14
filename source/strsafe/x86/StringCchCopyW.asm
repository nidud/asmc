; STRINGCCHCOPYW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCopyW proc pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR

    StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)

    mov ecx,pszDest
    mov edx,cchDest

    .ifs (SUCCEEDED(eax))

        StringCopyWorkerW(ecx,
                edx,
                NULL,
                pszSrc,
                STRSAFE_MAX_LENGTH)

    .elseif edx

        mov word ptr [ecx],0
    .endif
    ret

StringCchCopyW endp

    end
