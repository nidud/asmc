
include strsafe.inc

    .code

StringValidateDestAndLengthA proc pszDest:STRSAFE_LPCSTR, cchDest:size_t,
    pcchDestLength:ptr size_t, cchMax:size_t

    StringValidateDestA(rcx, rdx, r9)

    .ifs (SUCCEEDED(eax))

        StringLengthWorkerA(pszDest, cchDest, pcchDestLength)
    .else
        mov r8,pcchDestLength
        xor ecx,ecx
        mov [r8],rcx
    .endif
    ret

StringValidateDestAndLengthA endp

    end
