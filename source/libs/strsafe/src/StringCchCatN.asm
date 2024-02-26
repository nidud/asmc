; STRINGCCHCATN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCatN proc pszDest:LPTSTR, cchDest:size_t, pszSrc:LPTSTR, cchToAppend:size_t

  local hr:HRESULT
  local cchDestLength:size_t

    StringValidateDestAndLength(pszDest,
            cchDest,
            &cchDestLength,
            STRSAFE_MAX_CCH)

    .if (SUCCEEDED(eax))

        .if (cchToAppend > STRSAFE_MAX_LENGTH)

            mov eax,STRSAFE_E_INVALID_PARAMETER

        .else

            imul rax,cchDestLength,TCHAR
            add pszDest,rax
            sub cchDest,rax

            StringCopyWorker(pszDest, cchDest, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    ret

StringCchCatN endp

    end
