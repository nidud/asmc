; STRINGVALIDATEDEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringValidateDest proc pszDest:LPTSTR, cchDest:size_t, cchMax:size_t

    ldr rcx,cchMax
    ldr rdx,cchDest
    mov eax,S_OK

    .if ( !rdx || rdx > rcx )

        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif
    ret

StringValidateDest endp

    end
