; STRINGVALIDATEDESTANDLENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringValidateDestAndLength proc pszDest:LPCTSTR, cchDest:size_t,
    pcchDestLength:ptr size_t, cchMax:size_t

    StringValidateDest(pszDest, cchDest, cchMax)

    .if (SUCCEEDED(eax))

        StringLengthWorker(pszDest, cchDest, pcchDestLength)
    .else
        mov rdx,pcchDestLength
        xor ecx,ecx
        mov [rdx],rcx
    .endif
    ret

StringValidateDestAndLength endp

    end
