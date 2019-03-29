; STRINGCCHPRINTFW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchPrintfW proc pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszFormat:STRSAFE_LPCWSTR, argptr:vararg

    StringValidateDestW(rcx, rdx, STRSAFE_MAX_CCH)

    .if (SUCCEEDED(eax))

        StringVPrintfWorkerW(pszDest,
                cchDest,
                NULL,
                pszFormat,
                &argptr)

    .elseif (cchDest)

        mov rcx,pszDest
        mov word ptr [rcx],0
    .endif
    ret

StringCchPrintfW endp

    end
