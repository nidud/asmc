; STRINGEXVALIDATEDESTANDLENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringExValidateDestAndLength proc pszDest:LPCTSTR, cchDest:size_t,
        pcchDestLength:ptr size_t, cchMax:size_t, dwFlags:DWORD

    .new hr:HRESULT

    .if ( dwFlags & STRSAFE_IGNORE_NULLS )

        mov hr,StringExValidateDest(pszDest, cchDest, cchMax, dwFlags)

        .if ( FAILED(hr) || cchDest == 0 )

            mov rcx,pcchDestLength
            mov size_t ptr [rcx],0
        .else
            mov hr,StringLengthWorker(pszDest, cchDest, pcchDestLength)
        .endif
    .else
        mov hr,StringValidateDestAndLength(pszDest, cchDest, pcchDestLength, cchMax)
    .endif
    .return( hr )
    endp

    end
