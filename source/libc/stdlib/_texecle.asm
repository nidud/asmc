; _TEXECLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execle(char *cmdname, char *arg0, ... char *argn, NULL, char **envp);
; intptr_t _wexecle(wchar_t *cmdname, wchar_t *arg0, ... wchar_t *argn, NULL, char **envp);
;
include process.inc
include errno.inc
include tchar.inc

.code

_texecle proc name:tstring_t, arg0:tstring_t, argptr:vararg

    ldr rax,name

    .if ( rax && TCHAR ptr [rax] )

        ldr rax,arg0
    .endif
    .if ( !rax || TCHAR ptr [rax] == 0 )

        .return( _set_errno(EINVAL) )
    .endif

if not defined(_WIN64) or not defined(__UNIX__)

    .for ( eax = 0, rcx = &argptr : rax != [rcx] : rcx += tstring_t )
    .endf
    _texecve(name, &arg0, [rcx+tstring_t])

else

    mov     r10,rdi
    lea     rdi,argptr      ; 4 + rdi..r9 + xmm0..xmm7 = 26
    mov     r9,rdi
    stosq                   ; arg0
    mov     r8,[rdi]
    lea     rsi,[rdi+5*8]   ; rdx..r9

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
    lodsq
    _texecve(r10, r9, rax)
endif
    ret

_texecle endp

    end
