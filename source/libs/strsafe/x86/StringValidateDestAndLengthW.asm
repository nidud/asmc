; STRINGVALIDATEDESTANDLENGTHW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringValidateDestAndLengthW proc pszDest:STRSAFE_LPCWSTR, cchDest:size_t,
    pcchDestLength:ptr size_t, cchMax:size_t

    StringValidateDestW(pszDest, cchDest, cchMax)

    .ifs (SUCCEEDED(eax))

        StringLengthWorkerW(pszDest, cchDest, pcchDestLength)
    .else
        mov edx,pcchDestLength
        xor ecx,ecx
        mov [edx],ecx
    .endif
    ret

StringValidateDestAndLengthW endp

    end
