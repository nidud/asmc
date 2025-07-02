; _TPUTENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include errno.inc
include processenv.inc
include tchar.inc

.code

_tputenv proc uses rsi rbx string:tstring_t

   .new envp:tstring_t

    xor ebx,ebx
    .if ( _tcschr(string, '=') != NULL )

        mov tchar_t ptr [rax],0
        lea rbx,[rax+tchar_t]
    .endif
ifdef __UNIX__
    xor eax,eax
else
    SetEnvironmentVariable(string, rbx)
endif
    .if ( rbx )
        mov tchar_t ptr [rbx-tchar_t],'='
    .endif
    .if ( !eax )

        dec eax
       .return
    .endif
ifndef __UNIX__
    .if ( _tgetenvs() )

        mov rbx,_tenvptr
        mov _tenvptr,rax

        .if ( _tsetenvp( &envp ) )

            free(rbx)
            free(_tenviron)
            mov _tenviron,envp
            xor eax,eax

        .else

            free(_tenvptr)
            mov _tenvptr,rbx
            mov eax,-1
        .endif
    .else
        dec eax
    .endif
endif
    ret

_tputenv endp

    end
