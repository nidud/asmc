; STRINGCCHCOPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCopy proc pszDest:LPTSTR, cchDest:size_t, pszSrc:LPCTSTR

    StringValidateDest(pszDest, cchDest, STRSAFE_MAX_CCH)

    .if (SUCCEEDED(eax))

        StringCopyWorker(pszDest,
                cchDest,
                NULL,
                pszSrc,
                STRSAFE_MAX_LENGTH)

    .elseif cchDest

        mov rcx,pszDest
        mov TCHAR ptr [rcx],0
    .endif
    ret

StringCchCopy endp

    end
