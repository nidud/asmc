; STRINGCCHGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchGets proc pszDest:LPTSTR, cchDest:size_t

    .if ( SUCCEEDED( StringValidateDest(pszDest, cchDest, STRSAFE_MAX_CCH) ) )

        StringGetsWorker(pszDest, cchDest, NULL)

    .elseif ( cchDest )

        mov rcx,pszDest
        mov TCHAR ptr [rcx],0
    .endif
    ret
    endp

    end
