; STRINGCCHVPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchVPrintf proc _CRTIMP pszDest:LPTSTR, cchDest:size_t, pszFormat:LPTSTR, argList:ptr

    .if ( SUCCEEDED( StringValidateDest(pszDest, cchDest, STRSAFE_MAX_CCH) ) )

        StringVPrintfWorker(pszDest, cchDest, NULL, pszFormat, argList)

    .elseif ( cchDest )

        mov rcx,pszDest
        mov TCHAR ptr [rcx],0
    .endif
    ret

StringCchVPrintf endp

    end
