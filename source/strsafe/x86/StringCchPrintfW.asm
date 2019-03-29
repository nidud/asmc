; STRINGCCHPRINTFW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchPrintfW proc pszDest:STRSAFE_LPWSTR, cchDest:size_t, pszFormat:STRSAFE_LPCWSTR, argptr:vararg

  local hr:HRESULT

    mov hr,StringValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH)

    .if (SUCCEEDED(hr))

        mov hr,StringVPrintfWorkerW(pszDest,
                cchDest,
                NULL,
                pszFormat,
                &argptr)

    .elseif (cchDest)

        mov eax,pszDest
        mov word ptr [eax],0
    .endif

    mov eax,hr
    ret

StringCchPrintfW endp

    end
