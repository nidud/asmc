; _TEXECLPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _execlpe(char *cmdname, char *arg0, ... char *argn, NULL, char **envp);
; intptr_t _wexeclpe(wchar_t *cmdname, wchar_t *arg0, ... wchar_t *argn, NULL, wchar_t **envp);
;
include process.inc
include errno.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef execlpe
ALIAS <execlpe>=<_execlpe>
endif

.code

_texeclpe proc name:tstring_t, arg0:tstring_t, argptr:vararg

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
    _texecvpe(name, &arg0, [rcx+tstring_t])

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
    .if ( ecx == 5 )
        .for ( rsi = r8 : rax && ecx < 26 : ecx++ )

            lodsq
            stosq
        .endf
    .endif
    .if ( rax )

        .return( _set_errno(EINVAL) )
    .endif
    lodsq
    _texecvpe(r10, r9, rax)
endif
    ret

_texeclpe endp

    end
