; _TSPAWNLPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _spawnlpe(int mode, char *cmdname, char *arg0, char *arg1, ... char *argn, NULL, char **envp);
; intptr_t _wspawnlpe(int mode, wchar_t *cmdname, wchar_t *arg0, wchar_t *arg1, ... wchar_t *argn, NULL, wchar_t **envp);
;
include process.inc
include errno.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef spawnlpe
ALIAS <spawnlpe>=<_spawnlpe>
endif

.code

_tspawnlpe proc mode:int_t, name:tstring_t, arg0:tstring_t, argptr:vararg

    ldr rax,name
    .if ( rax && tchar_t ptr [rax] )
        ldr rax,arg0
    .endif
    .if ( !rax || tchar_t ptr [rax] == 0 )
        .return( _set_errno(EINVAL) )
    .endif

if not defined(_WIN64) or not defined(__UNIX__)

    .for ( eax = 0, rcx = &argptr : rax != [rcx] : rcx += tstring_t )
    .endf
    _tspawnvpe( mode, name, &arg0, [rcx+tstring_t] )

else

    mov     r10,rdi
    mov     r11,rsi
    lea     rdi,argptr
    mov     r9,rdi
    stosq
    mov     r8,[rdi]
    lea     rsi,[rdi+6*8]

    .for ( edx = 1 : rax && edx < 4 : edx++ )

        lodsq ; rcx..r9
        stosq
    .endf
    .if ( edx == 4 )

        .for ( rsi = r8 : rax && edx < 26 : edx++ )

            lodsq ; arg4..argn
            stosq
        .endf
    .endif
    .if ( rax )

        .return( _set_errno(EINVAL) )
    .endif
    lodsq
    _tspawnvpe( r10d, r11, r9, rax )
endif
    ret

_tspawnlpe endp

    end
