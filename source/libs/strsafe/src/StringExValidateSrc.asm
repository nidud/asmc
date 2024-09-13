; STRINGEXVALIDATESRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringExValidateSrc proc _CRTIMP uses rbx ppszSrc:ptr LPTSTR, pcchToRead:ptr size_t, cchMax:size_t, dwFlags:DWORD

    ldr rcx,ppszSrc
    ldr rbx,cchMax
    ldr rdx,pcchToRead
    mov eax,S_OK

    .if ( rdx && [rdx] >= rbx )

        mov eax,STRSAFE_E_INVALID_PARAMETER

    .elseif ( dwFlags & STRSAFE_IGNORE_NULLS && [rcx] == rax )

        mov [rcx],&@CStr("")
        .if ( rdx )
            mov [rdx],rax
        .endif
    .endif
    ret

StringExValidateSrc endp

    end
