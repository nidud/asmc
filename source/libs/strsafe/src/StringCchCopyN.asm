; STRINGCCHCOPYN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCopyN proc pszDest:LPTSTR,
        cchDest:size_t, pszSrc:LPTSTR, cchToCopy:size_t

    StringValidateDest(pszDest, cchDest, STRSAFE_MAX_CCH)

    mov rcx,pszDest
    mov rdx,cchDest

    .ifs (SUCCEEDED(eax))

        .if ( cchToCopy > STRSAFE_MAX_LENGTH )

            mov eax,STRSAFE_E_INVALID_PARAMETER
            mov TCHAR ptr [rcx],0
        .else

            StringCopyWorker(pszDest, cchDest, NULL, pszSrc, cchToCopy)
        .endif

    .elseif rdx

        mov TCHAR ptr [rcx],0
    .endif
    ret

StringCchCopyN endp

    end
