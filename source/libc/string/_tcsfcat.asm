; _TCSFCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strfcat(char *, char *, char *);
; wchar_t *_wstrfcat(wchar_t *, wchar_t *, wchar_t *);
;
include string.inc
include tchar.inc

    .code

_tcsfcat proc uses rsi rdi rbx buffer:LPTSTR, path:LPTSTR, file:LPTSTR

    ldr rsi,path
    ldr rbx,file
    ldr rdx,buffer

    xor eax,eax
    mov ecx,-1

    .if ( rsi )

        mov   rdi,rsi ; overwrite buffer
        repne _tscasb
        mov   rdi,rdx
        not   ecx
        rep   _tmovsb
    .else
        mov   rdi,rdx ; length of buffer
        repne _tscasb
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
           _tstosb
        .endif
    .endif

    mov rsi,rbx ; add file name
    .repeat
       _tlodsb
       _tstosb
    .until !eax
    .return(rdx)

_tcsfcat endp

    end
