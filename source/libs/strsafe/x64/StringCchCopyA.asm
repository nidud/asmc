; STRINGCCHCOPYA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCchCopyA proc pszDest:STRSAFE_LPSTR, cchDest:size_t, pszSrc:STRSAFE_LPCSTR

    StringValidateDestA(rcx, rdx, STRSAFE_MAX_CCH)

    mov rcx,pszDest
    mov rdx,cchDest

    .ifs (SUCCEEDED(eax))

        StringCopyWorkerA(rcx,
                rdx,
                NULL,
                pszSrc,
                STRSAFE_MAX_LENGTH)

    .elseif rdx

        mov byte ptr [rcx],0
    .endif
    ret

StringCchCopyA endp

    end
