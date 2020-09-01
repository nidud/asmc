; STRINGCCHPRINTFA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchPrintfA proc pszDest:STRSAFE_LPSTR, cchDest:size_t, pszFormat:STRSAFE_LPCSTR, argptr:vararg

  local hr:HRESULT

    mov hr,StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)

    .if (SUCCEEDED(hr))

        mov hr,StringVPrintfWorkerA(pszDest,
                cchDest,
                NULL,
                pszFormat,
                &argptr)

    .elseif (cchDest)

        mov eax,pszDest
        mov byte ptr [eax],0
    .endif

    mov eax,hr
    ret

StringCchPrintfA endp

    end
