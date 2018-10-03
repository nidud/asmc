
include strsafe.inc

    .code

StringCchCatW proc pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszSrc:STRSAFE_LPCWSTR

  local hr:HRESULT
  local cchDestLength:size_t

    StringValidateDestAndLengthW(pszDest,
            cchDest,
            &cchDestLength,
            STRSAFE_MAX_CCH)

    .ifs (SUCCEEDED(eax))

        mov rcx,pszDest
        add rcx,cchDestLength
        mov rdx,cchDest
        sub rdx,cchDestLength

        StringCopyWorkerW(rcx, rdx, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .endif
    ret

StringCchCatW endp

    end
