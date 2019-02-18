; STRINGCCHPRINTFA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchPrintfA proc pszDest:STRSAFE_LPSTR, cchDest:size_t, pszFormat:STRSAFE_LPCSTR, argptr:vararg

    StringValidateDestA(rcx, rdx, STRSAFE_MAX_CCH)

    .if (SUCCEEDED(eax))

        StringVPrintfWorkerA(pszDest,
                cchDest,
                NULL,
                pszFormat,
                &argptr)

    .elseif (cchDest)

        mov rcx,pszDest
        mov byte ptr [rcx],0
    .endif
    ret

StringCchPrintfA endp

    end
