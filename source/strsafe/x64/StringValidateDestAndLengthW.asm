; STRINGVALIDATEDESTANDLENGTHW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringValidateDestAndLengthW proc pszDest:STRSAFE_LPCWSTR, cchDest:size_t,
    pcchDestLength:ptr size_t, cchMax:size_t

    StringValidateDestW(rcx, rdx, r9)

    .ifs (SUCCEEDED(eax))

        StringLengthWorkerW(pszDest, cchDest, pcchDestLength)
    .else
        mov r8,pcchDestLength
        xor ecx,ecx
        mov [r8],rcx
    .endif
    ret

StringValidateDestAndLengthW endp

    end
