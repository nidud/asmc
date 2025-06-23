; STRINGEXHANDLEFILLBEHINDNULL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringExHandleFillBehindNull proc _CRTIMP pszDestEnd:LPTSTR, cbRemaining:size_t, dwFlags:DWORD

    ldr eax,dwFlags
    ldr rcx,pszDestEnd
    ldr rdx,cbRemaining

    .if ( rdx > TCHAR )

        add  rcx,TCHAR
        sub  rdx,TCHAR
        xchg rcx,rdx
        xchg rdx,rdi
        rep  stosb
        mov  rdi,rdx
    .endif
    xor eax,eax
    ret

StringExHandleFillBehindNull endp

    end
