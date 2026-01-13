; STRINGEXVALIDATEDEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringExValidateDest proc pszDest:LPTSTR, cchDest:size_t, cchMax:size_t, dwFlags:DWORD

    .new hr:HRESULT = S_OK

    .if ( dwFlags & STRSAFE_IGNORE_NULLS )

        .if ( ( ( pszDest == NULL ) && ( cchDest != 0 ) ) || ( cchDest > cchMax ) )

            mov hr,STRSAFE_E_INVALID_PARAMETER
        .endif
    .else
        mov hr,StringValidateDest(pszDest, cchDest, cchMax)
    .endif
    .return( hr )
    endp

    end
