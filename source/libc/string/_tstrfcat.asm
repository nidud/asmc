; _TSTRFCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tstrfcat proc uses rbx rsi rdi buffer:LPTSTR, path:LPTSTR, file:LPTSTR

    ldr rsi,path
    ldr rbx,file
    ldr rdx,buffer

    xor eax,eax
    mov ecx,-1

    .if ( rsi )

        mov   rdi,rsi ; overwrite buffer
        repne .scasb
        mov   rdi,rdx
        not   ecx
        rep   .movsb
    .else
        mov   rdi,rdx ; length of buffer
        repne .scasb
    .endif
    sub rdi,TCHAR

    .if ( rdi != rdx ) ; add slash if missing

        movzx eax,TCHAR ptr [rdi-TCHAR]
ifdef __UNIX__
        .if ( eax != '/' )

            mov eax,'/'
else
        .if ( !( eax == '\' || eax == '/' ) )

            mov eax,'\'
endif
           .stosb
        .endif
    .endif

    mov rsi,rbx ; add file name
    .repeat
       .lodsb
       .stosb
    .until !eax
    .return(rdx)

_tstrfcat endp

    end
