; STRINGCCHCATN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCatN proc _CRTIMP pszDest:LPTSTR, cchDest:size_t, pszSrc:LPTSTR, cchToAppend:size_t

    .new cchDestLength:size_t

    .if ( SUCCEEDED(StringValidateDestAndLength(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH)) )

        .if ( cchToAppend > STRSAFE_MAX_LENGTH )

            mov eax,STRSAFE_E_INVALID_PARAMETER
        .else
            mov rcx,cchDestLength
            sub cchDest,rcx
ifdef _UNICODE
            add rcx,rcx
endif
            add rcx,pszDest
            StringCopyWorker(rcx, cchDest, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    ret

StringCchCatN endp

    end
