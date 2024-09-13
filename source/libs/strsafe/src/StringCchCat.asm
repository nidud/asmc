; STRINGCCHCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCat proc _CRTIMP pszDest:LPTSTR, cchDest:size_t, pszSrc:LPCTSTR

    .new cchDestLength:size_t

    .if ( SUCCEEDED( StringValidateDestAndLength(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH) ) )

        sub cchDest,cchDestLength
ifdef _UNICODE
        add rax,rax
endif
        add pszDest,rax
        StringCopyWorker(pszDest, cchDest, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .endif
    ret

StringCchCat endp

    end
