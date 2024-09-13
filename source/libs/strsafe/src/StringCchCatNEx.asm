; STRINGCCHCATNEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

    .code

StringCchCatNEx proc _CRTIMP pszDest:LPTSTR, cchDest:size_t, pszSrc:LPTSTR, cchToAppend:size_t,
        ppszDestEnd:LPTSTR, pcchRemaining:ptr size_t, dwFlags:DWORD

   .new hr:HRESULT
   .new cchDestLength:size_t

    mov hr,StringExValidateDestAndLength(pszDest, cchDest, &cchDestLength, STRSAFE_MAX_CCH, dwFlags)

    .if (SUCCEEDED(hr))

       .new pszDestEnd:LPTSTR
       .new cchRemaining:size_t

        mov rax,cchDestLength
        mov rcx,cchDest
        sub rcx,rax
        mov cchRemaining,rcx
ifdef _UNICODE
        add rax,rax
endif
        add rax,pszDest
        mov pszDestEnd,rax
        mov hr,StringExValidateSrc(&pszSrc, &cchToAppend, STRSAFE_MAX_CCH, dwFlags)

        .if (SUCCEEDED(hr))

            .if ( dwFlags & ( not STRSAFE_VALID_FLAGS ) )

                mov hr,STRSAFE_E_INVALID_PARAMETER

            .elseif ( cchRemaining <= 1 )

                ; only fail if there was actually src data to append

                mov rcx,pszSrc
                .if ( cchToAppend && TCHAR ptr [rcx] )

                    .if ( pszDest == NULL )

                        mov hr,STRSAFE_E_INVALID_PARAMETER
                    .else
                        mov hr,STRSAFE_E_INSUFFICIENT_BUFFER
                    .endif
                .endif

            .else

               .new cchCopied:size_t = 0

                mov hr,StringCopyWorker(pszDestEnd, cchRemaining, &cchCopied, pszSrc, cchToAppend)
                mov rcx,cchCopied
                sub cchRemaining,rcx
ifdef _UNICODE
                add rcx,rcx
endif
                add pszDestEnd,rcx
                mov rdx,cchRemaining

                .if ( SUCCEEDED(hr) && ( dwFlags & STRSAFE_FILL_BEHIND_NULL ) && rdx > 1 )

                    ; safe to multiply cchRemaining * TCHAR since cchRemaining < STRSAFE_MAX_CCH

                    imul rax,rdx,TCHAR

                    ; handle the STRSAFE_FILL_BEHIND_NULL flag

                    StringExHandleFillBehindNull(pszDestEnd, rax, dwFlags)
                .endif
            .endif
        .endif

        .if ( FAILED(hr) &&
              ( dwFlags & ( STRSAFE_NO_TRUNCATION or STRSAFE_FILL_ON_FAILURE or STRSAFE_NULL_ON_FAILURE ) ) &&
              ( cchDest != 0 ) )

           .new cbDest:size_t

            ; safe to multiply cchDest * TCHAR since cchDest < STRSAFE_MAX_CCH

            imul rax,cchDest,TCHAR
            mov cbDest,rax

            ; handle the STRSAFE_FILL_ON_FAILURE, STRSAFE_NULL_ON_FAILURE, and STRSAFE_NO_TRUNCATION flags

            StringExHandleOtherFlags(pszDest, cbDest, cchDestLength, &pszDestEnd, &cchRemaining, dwFlags)
        .endif

        .if ( SUCCEEDED(hr) || ( hr == STRSAFE_E_INSUFFICIENT_BUFFER ) )

            mov rcx,ppszDestEnd
            .if ( rcx )

                mov rax,pszDestEnd
                mov [rcx],rax
            .endif

            mov rcx,pcchRemaining
            .if ( rcx )

                mov rax,cchRemaining
                mov [rcx],rax
            .endif
        .endif
    .endif
    .return( hr )

StringCchCatNEx endp

    end
