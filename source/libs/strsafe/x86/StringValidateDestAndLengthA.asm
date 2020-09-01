; STRINGVALIDATEDESTANDLENGTHA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringValidateDestAndLengthA proc WINAPI pszDest:STRSAFE_LPCSTR, cchDest:size_t,
    pcchDestLength:ptr size_t, cchMax:size_t

    StringValidateDestA(pszDest, cchDest, cchMax)

    .ifs (SUCCEEDED(eax))

        StringLengthWorkerA(pszDest, cchDest, pcchDestLength)
    .else
        mov edx,pcchDestLength
        xor ecx,ecx
        mov [edx],ecx
    .endif
    ret

StringValidateDestAndLengthA endp

    end
