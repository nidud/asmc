; STRINGVALIDATEDESTANDLENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringValidateDestAndLength proc _CRTIMP uses rbx pszDest:LPCTSTR, cchDest:size_t, pcchDestLength:ptr size_t, cchMax:size_t

    ldr rax,pszDest
    ldr rbx,pcchDestLength
ifdef __UNIX__
    ldr rdx,cchMax
    ldr rcx,cchDest
else
    ldr rcx,cchDest
    ldr rdx,cchMax
endif
    .if ( !rcx || rcx > rdx )

        xor eax,eax
        mov [rbx],rax
        mov eax,STRSAFE_E_INVALID_PARAMETER

    .else

        .for ( rdx = rcx : rcx && ( TCHAR ptr [rax] != 0 ) : rcx-- )

            add rax,TCHAR
        .endf
        xor eax,eax
        .if ( !rcx )

            ; the string is longer than cchMax

            mov rdx,rcx
            mov eax,STRSAFE_E_INVALID_PARAMETER
        .endif
        sub rdx,rcx
        mov rcx,rdx
        mov [rbx],rcx
    .endif
    ret

StringValidateDestAndLength endp

    end
