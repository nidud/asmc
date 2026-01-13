; STRINGEXHANDLEOTHERFLAGS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringExHandleOtherFlags proc uses rbx pszDest:LPTSTR, cbDest:size_t, cchOriginalDestLength:size_t, ppszDestEnd:ptr LPTSTR, pcchRemaining:ptr size_t, dwFlags:DWORD

   .new cchDest:size_t

    ldr rbx,pszDest
    .if !( dwFlags & ( STRSAFE_NO_TRUNCATION or STRSAFE_FILL_ON_FAILURE or STRSAFE_NULL_ON_FAILURE ) )

        .return( STRSAFE_E_INVALID_PARAMETER )
    .endif

    mov rdx,cbDest
ifdef _UNICODE
    shr rdx,1
endif
    mov cchDest,rdx

    .if ( ( rdx > 0 ) && ( dwFlags & STRSAFE_NO_TRUNCATION ) )

        mov rax,cchOriginalDestLength
ifdef _UNICODE
        add rax,rax
endif
        add rax,rbx
        mov rcx,ppszDestEnd
        mov [rcx],rax
        sub rdx,cchOriginalDestLength
        mov rcx,pcchRemaining
        mov [rcx],rdx

        ; null terminate the end of the original string

        mov TCHAR ptr [rax],0
    .endif

    .if ( dwFlags & STRSAFE_FILL_ON_FAILURE )

        memset(rbx, STRSAFE_GET_FILL_PATTERN(dwFlags), cbDest)

        .if ( STRSAFE_GET_FILL_PATTERN(dwFlags) == 0 )

            mov rax,ppszDestEnd
            mov [rax],rbx
            mov rcx,pcchRemaining
            mov rax,cchDest
            mov [rcx],rax
            .if ( TCHAR ptr [rbx] != 0 )

                .return( STRSAFE_E_INVALID_PARAMETER )
            .endif

        .elseif ( cchDest > 0 )

            mov rcx,cbDest
            lea rcx,[rbx+rcx-TCHAR]
            mov rdx,ppszDestEnd
            mov [rdx],rcx
            mov rdx,pcchRemaining
            mov size_t ptr [rdx],1

            ; null terminate the end of the string

            mov TCHAR ptr [rcx],0
        .endif
    .endif

    .if ( ( cchDest > 0 ) && ( dwFlags & STRSAFE_NULL_ON_FAILURE ) )

        mov rax,ppszDestEnd
        mov [rax],rbx
        mov rax,pcchRemaining
        mov rdx,cchDest
        mov [rax],rdx

        ; null terminate the beginning of the string

        mov TCHAR ptr [rbx],0
    .endif
    .return( S_OK )
    endp

    end
