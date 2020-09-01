; STRINGCCHCATA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCatA proc pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR

  local hr:HRESULT
  local cchDestLength:size_t

    StringValidateDestAndLengthA(pszDest,
            cchDest,
            &cchDestLength,
            STRSAFE_MAX_CCH)

    .ifs (SUCCEEDED(eax))

        mov ecx,pszDest
        add ecx,cchDestLength
        mov edx,cchDest
        sub edx,cchDestLength

        StringCopyWorkerA(ecx, edx, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .endif
    ret

StringCchCatA endp

    end
