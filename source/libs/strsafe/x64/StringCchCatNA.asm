; STRINGCCHCATNA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCatNA proc pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR, cchToAppend:size_t

  local hr:HRESULT
  local cchDestLength:size_t

    StringValidateDestAndLengthA(pszDest,
            cchDest,
            &cchDestLength,
            STRSAFE_MAX_CCH)

    .ifs (SUCCEEDED(eax))

        .if (cchToAppend > STRSAFE_MAX_LENGTH)

            mov eax,STRSAFE_E_INVALID_PARAMETER

        .else

            mov rcx,pszDest
            add rcx,cchDestLength
            mov rdx,cchDest
            sub rdx,cchDestLength

            StringCopyWorkerW(rcx, rdx, NULL, pszSrc, cchToAppend)
        .endif
    .endif
    ret

StringCchCatNA endp

    end
