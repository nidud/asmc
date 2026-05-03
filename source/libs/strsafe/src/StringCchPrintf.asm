; STRINGCCHPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchPrintf proc pszDest:LPTSTR, cchDest:size_t, pszFormat:LPTSTR, argptr:vararg

    .if ( SUCCEEDED( StringValidateDest(pszDest, cchDest, STRSAFE_MAX_CCH) ) )

        StringVPrintfWorker(pszDest, cchDest, NULL, pszFormat, &argptr)

    .elseif ( cchDest )

        mov rcx,pszDest
        mov TCHAR ptr [rcx],0
    .endif
    ret
    endp

    end
