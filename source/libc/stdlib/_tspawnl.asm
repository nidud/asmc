; _TSPAWNL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _spawnl(int mode, char *cmdname, char *arg0, char *arg1, ... char *argn, NULL);
; intptr_t _wspawnl(int mode, wchar_t *cmdname, wchar_t *arg0, wchar_t *arg1, ... wchar_t *argn, NULL);
;
include process.inc
include errno.inc
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef spawnl
ALIAS <spawnl>=<_spawnl>
endif

.code

_tspawnl proc mode:int_t, name:tstring_t, arg0:tstring_t, argptr:vararg

    ldr rax,name
    .if ( rax && TCHAR ptr [rax] )
        ldr rax,arg0
    .endif
    .if ( !rax || TCHAR ptr [rax] == 0 )
        .return( _set_errno(EINVAL) )
    .endif

if not defined(_WIN64) or not defined(__UNIX__)

    _tspawnve( mode, name, &arg0, _tenviron )

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

    .for ( rsi = r8 : rax && edx < 26 : edx++ )

        lodsq ; arg4..argn
        stosq
    .endf

    .if ( rax )

        .return( _set_errno(EINVAL) )
    .endif
    _tspawnve( r10d, r11, r9, _tenviron )
endif
    ret

_tspawnl endp

    end
