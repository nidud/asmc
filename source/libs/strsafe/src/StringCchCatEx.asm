; STRINGCCHCATEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCatEx proc pszDest:LPTSTR, cchDest:size_t, pszSrc:LPCTSTR,
        ppszDestEnd:LPTSTR, pcchRemaining:ptr size_t, dwFlags:DWORD

   .new hr:HRESULT
   .new cchDestLength:size_t

    mov hr,StringExValidateDestAndLength(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH, dwFlags)

    .if (SUCCEEDED(hr))

        .new pszDestEnd:LPTSTR
        .new cchRemaining:size_t

        mov rax,cchDestLength
ifdef _UNICODE
        add rax,rax
endif
        add rax,pszDest
        mov pszDestEnd,rax
        mov rax,cchDest
        sub rax,cchDestLength
        mov cchRemaining,rax

        mov hr,StringExValidateSrc(&pszSrc, NULL, STRSAFE_MAX_CCH, dwFlags)

        .if (SUCCEEDED(hr))

            .if (dwFlags & (not STRSAFE_VALID_FLAGS))

                mov hr,STRSAFE_E_INVALID_PARAMETER

            .elseif ( cchRemaining <= 1 )

                ; only fail if there was actually src data to append

                mov rax,pszSrc
                .if ( TCHAR ptr [rax] )

                    .if ( pszDest == NULL )
                        mov hr,STRSAFE_E_INVALID_PARAMETER
                    .else
                        mov hr,STRSAFE_E_INSUFFICIENT_BUFFER
                    .endif
                .endif

            .else

               .new cchCopied:size_t = 0

                mov hr,StringCopyWorker(pszDestEnd, cchRemaining, &cchCopied, pszSrc, STRSAFE_MAX_LENGTH)
                mov rax,cchCopied
                sub cchRemaining,rax
ifdef _UNICODE
                add rax,rax
endif
                add pszDestEnd,rax

                .if (SUCCEEDED(hr) && (dwFlags & STRSAFE_FILL_BEHIND_NULL) && (cchRemaining > 1))

                   .new cbRemaining:size_t
                    mov rax,cchRemaining
ifdef _UNICODE
                    add rax,rax
endif
                    ; safe to multiply cchRemaining * sizeof(char) since cchRemaining < STRSAFE_MAX_CCH and sizeof(char) is 1

                    mov cbRemaining,rax

                    ; handle the STRSAFE_FILL_BEHIND_NULL flag

                    StringExHandleFillBehindNull(pszDestEnd, cbRemaining, dwFlags)
                .endif
            .endif
        .endif

        .if ( FAILED(hr) && (dwFlags & (STRSAFE_NO_TRUNCATION or STRSAFE_FILL_ON_FAILURE or STRSAFE_NULL_ON_FAILURE)) && cchDest )

           .new cbDest:size_t

            ; safe to multiply cchDest * sizeof(char) since cchDest < STRSAFE_MAX_CCH and sizeof(char) is 1

            mov rax,cchDest
ifdef _UNICODE
            add rax,rax
endif
            mov cbDest,rax

            ; handle the STRSAFE_FILL_ON_FAILURE, STRSAFE_NULL_ON_FAILURE, and STRSAFE_NO_TRUNCATION flags

            StringExHandleOtherFlags(pszDest, cbDest, cchDestLength, &pszDestEnd, &cchRemaining, dwFlags)
        .endif

        .if ( SUCCEEDED(hr) || hr == STRSAFE_E_INSUFFICIENT_BUFFER )

            mov rax,ppszDestEnd
            .if ( rax )

                mov rcx,pszDestEnd
                mov [rax],rcx
            .endif
            mov rax,pcchRemaining
            .if ( rax )

                mov rcx,cchRemaining
                mov [rax],rcx
            .endif
        .endif
    .endif
    .return( hr )
    endp

    end
