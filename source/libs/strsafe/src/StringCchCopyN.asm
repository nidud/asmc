; STRINGCCHCOPYN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCopyN proc _CRTIMP pszDest:LPTSTR, cchDest:size_t, pszSrc:LPTSTR, cchToCopy:size_t

    .if ( SUCCEEDED( StringValidateDest(pszDest, cchDest, STRSAFE_MAX_CCH) ) )

        .if ( cchToCopy > STRSAFE_MAX_LENGTH )

            mov eax,STRSAFE_E_INVALID_PARAMETER
            mov rcx,pszDest
            mov TCHAR ptr [rcx],0
        .else
            StringCopyWorker(pszDest, cchDest, NULL, pszSrc, cchToCopy)
        .endif

    .elseif ( cchDest )

        mov rcx,pszDest
        mov TCHAR ptr [rcx],0
    .endif
    ret

StringCchCopyN endp

    end
