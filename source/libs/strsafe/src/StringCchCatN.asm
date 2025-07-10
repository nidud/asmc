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
            mov rax,cchDestLength
            sub cchDest,rax
ifdef _UNICODE
            add rax,rax
endif
            add pszDest,rax
            StringCopyWorker(pszDest, cchDest, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    ret

StringCchCatN endp

    end
