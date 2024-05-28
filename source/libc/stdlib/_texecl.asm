; _TEXECL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execl(char *cmdname, char *arg0, ... char *argn, NULL);
; intptr_t _wexecl(wchar_t *cmdname, wchar_t *arg0, ... wchar_t *argn, NULL);
;
include process.inc
include errno.inc
include tchar.inc

.code

_texecl proc name:tstring_t, arg0:tstring_t, argptr:vararg

    ldr rax,name

    .if ( rax && TCHAR ptr [rax] )

        ldr rax,arg0
    .endif
    .if ( !rax || TCHAR ptr [rax] == 0 )

        .return( _set_errno(EINVAL) )
    .endif

if not defined(_WIN64) or not defined(__UNIX__)

    _texecve(name, &arg0, NULL)

else

    mov     rcx,rdi
    lea     rdi,argptr
    mov     r9,rdi
    stosq
    mov     r8,[rdi]
    lea     rsi,[rdi+5*8]

    .for ( edx = 1 : rax && edx < 5 : edx++ )

        lodsq
        stosq
    .endf

    .for ( rsi = r8 : rax && edx < 26 : edx++ )

        lodsq
        stosq
    .endf

    .if ( rax )

        .return( _set_errno(EINVAL) )
    .endif
    _texecve(rcx, r9, rax)
endif
    ret

_texecl endp

    end
