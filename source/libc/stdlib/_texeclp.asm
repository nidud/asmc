; _TEXECLP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execlp(char *cmdname, char *arg0, ... char *argn, NULL);
; intptr_t _wexeclp(wchar_t *cmdname, wchar_t *arg0, ... wchar_t *argn, NULL);
;
include process.inc
include errno.inc
include tchar.inc

.code

_texeclp proc name:tstring_t, arg0:tstring_t, argptr:vararg

    ldr rax,name

    .if ( rax && TCHAR ptr [rax] )

        ldr rax,arg0
    .endif
    .if ( !rax || TCHAR ptr [rax] == 0 )

        .return( _set_errno(EINVAL) )
    .endif

if not defined(_WIN64) or not defined(__UNIX__)

    _texecvp(name, &arg0)

else

    mov     rdx,rdi
    lea     rdi,argptr
    mov     r9,rdi
    stosq
    mov     r8,[rdi]
    lea     rsi,[rdi+5*8]

    .for ( ecx = 1 : rax && ecx < 5 : ecx++ )

        lodsq
        stosq
    .endf

    .for ( rsi = r8 : rax && ecx < 26 : ecx++ )

        lodsq
        stosq
    .endf

    .if ( rax )

        .return( _set_errno(EINVAL) )
    .endif
    _texecvp(rdx, r9)
endif
    ret

_texeclp endp

    end
