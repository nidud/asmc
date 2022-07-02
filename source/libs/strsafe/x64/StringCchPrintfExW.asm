; STRINGCCHPRINTFEXW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchPrintfExW proc uses rsi rdi rbx pszDest:STRSAFE_LPWSTR,
    cchDest:size_t,
    ppszDestEnd:ptr STRSAFE_LPWSTR,
    pcchRemaining: ptr size_t,
    dwFlags:DWORD,
    pszFormat:STRSAFE_LPCWSTR,
    args:vararg

    local hr:HRESULT

    mov hr,StringExValidateDestW(pszDest, cchDest, STRSAFE_MAX_CCH, dwFlags)

    .if (SUCCEEDED(hr))

        .new pszDestEnd:STRSAFE_LPWSTR = pszDest
        .new cchRemaining:size_t = cchDest

        mov hr,StringExValidateSrcW(&pszFormat, NULL, STRSAFE_MAX_CCH, dwFlags)

        .if (SUCCEEDED(hr))

            .if (dwFlags & (not STRSAFE_VALID_FLAGS))

                mov hr,STRSAFE_E_INVALID_PARAMETER

                .if (cchDest != 0)

                    mov rcx,pszDest
                    mov word ptr [rcx],0
                .endif

            .elseif (cchDest == 0)

                ;; only fail if there was actually a non-empty format string
                mov rcx,pszFormat
                .if (word ptr [rcx] != 0)

                    .if (pszDest == NULL)

                        mov hr,STRSAFE_E_INVALID_PARAMETER

                    .else

                        mov hr,STRSAFE_E_INSUFFICIENT_BUFFER
                    .endif
                .endif

            .else

                .new cchNewDestLength:size_t = 0

                mov hr,StringVPrintfWorkerW(pszDest,
                                          cchDest,
                                          &cchNewDestLength,
                                          pszFormat,
                                          args)

                mov rax,pszDest
                add rax,cchNewDestLength
                mov pszDestEnd,rax
                mov rax,cchDest
                sub rax,cchNewDestLength
                mov cchRemaining,rax

                .if (SUCCEEDED(hr) && (dwFlags & STRSAFE_FILL_BEHIND_NULL) && (cchRemaining > 1))

                    .new cbRemaining:size_t

                    ;; safe to multiply cchRemaining * sizeof(wchar_t) since cchRemaining < STRSAFE_MAX_CCH and sizeof(wchar_t) is 2
                    imul rax,cchRemaining,sizeof(wchar_t)
                    mov cbRemaining,rax

                    ;; handle the STRSAFE_FILL_BEHIND_NULL flag
                    StringExHandleFillBehindNullW(pszDestEnd, cbRemaining, dwFlags)
                .endif
            .endif

        .else

            .if (cchDest != 0)

                mov rcx,pszDest
                mov word ptr [rcx],0
            .endif
        .endif

        .if ((FAILED(hr)) && \
            (dwFlags & (STRSAFE_NO_TRUNCATION or STRSAFE_FILL_ON_FAILURE or STRSAFE_NULL_ON_FAILURE)) && \
            (cchDest != 0))

            .new cbDest:size_t

            ;; safe to multiply cchDest * sizeof(wchar_t) since cchDest < STRSAFE_MAX_CCH and sizeof(wchar_t) is 2
            imul rax,cchDest,sizeof(wchar_t)
            mov cbDest,rax

            ;; handle the STRSAFE_FILL_ON_FAILURE, STRSAFE_NULL_ON_FAILURE, and STRSAFE_NO_TRUNCATION flags
            StringExHandleOtherFlagsW(pszDest,
                                      cbDest,
                                      0,
                                      &pszDestEnd,
                                      &cchRemaining,
                                      dwFlags)
        .endif

        .if (SUCCEEDED(hr) || (hr == STRSAFE_E_INSUFFICIENT_BUFFER))

            .if (ppszDestEnd)

                mov rcx,ppszDestEnd
                mov rax,pszDestEnd
                mov [rcx],rax
            .endif

            .if (pcchRemaining)

                mov rcx,pcchRemaining
                mov rax,cchRemaining
                mov [rcx],rax
            .endif
        .endif
    .endif

    mov eax,hr
    ret
StringCchPrintfExW endp

    end
