; STRINGCCHCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCat proc pszDest:LPTSTR, cchDest:size_t, pszSrc:LPCTSTR

  local hr:HRESULT
  local cchDestLength:size_t

    StringValidateDestAndLength(pszDest,
            cchDest,
            &cchDestLength,
            STRSAFE_MAX_CCH)

    .ifs (SUCCEEDED(eax))

        imul rax,cchDestLength,TCHAR
        add pszDest,rax
        sub cchDest,rax

        StringCopyWorker(pszDest, cchDest, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .endif
    ret

StringCchCat endp

    end
