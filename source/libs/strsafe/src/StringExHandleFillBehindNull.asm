; STRINGEXHANDLEFILLBEHINDNULL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringExHandleFillBehindNull proc _CRTIMP pszDestEnd:LPTSTR, cbRemaining:size_t, dwFlags:DWORD

    ldr rcx,pszDestEnd
    ldr eax,dwFlags
    ldr rdx,cbRemaining

    .if ( rdx > TCHAR )

        add rcx,TCHAR
        sub rdx,TCHAR
        memset(rcx, STRSAFE_GET_FILL_PATTERN(eax), rdx)
    .endif
    .return( S_OK )

StringExHandleFillBehindNull endp

    end
