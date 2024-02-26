; STRINGCCHPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchPrintf proc pszDest:LPTSTR, cchDest:size_t, pszFormat:LPTSTR, argptr:vararg

    StringValidateDest(pszDest, cchDest, STRSAFE_MAX_CCH)

    .if (SUCCEEDED(eax))

        StringVPrintfWorker(pszDest,
                cchDest,
                NULL,
                pszFormat,
                &argptr)

    .elseif ( cchDest )

        mov rcx,pszDest
        mov TCHAR ptr [rcx],0
    .endif
    ret

StringCchPrintf endp

    end
