; STRINGCCHCOPYA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCopyA proc pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR

    StringValidateDestA(pszDest, cchDest, STRSAFE_MAX_CCH)

    mov ecx,pszDest
    mov edx,cchDest

    .ifs (SUCCEEDED(eax))

        StringCopyWorkerA(ecx, edx, NULL, pszSrc, STRSAFE_MAX_LENGTH)

    .elseif edx

        mov byte ptr [ecx],0
    .endif
    ret

StringCchCopyA endp

    end
