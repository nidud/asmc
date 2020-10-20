; STRINGCCHCATW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
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

        mov rax,cchDestLength
        add rax,rax
        mov rcx,pszDest
        add rcx,rax
        mov rdx,cchDest
        sub rdx,rax

        StringCopyWorkerW(rcx, rdx, NULL, pszSrc, STRSAFE_MAX_LENGTH)
    .endif
    ret

StringCchCatW endp

    end
