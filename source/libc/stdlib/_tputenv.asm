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

_tputenv proc uses rsi rbx string:LPTSTR

   .new envp:LPTSTR

    xor ebx,ebx
    .if ( _tcschr(string, '=') != NULL )

        mov TCHAR ptr [rax],0
        lea rbx,[rax+TCHAR]
    .endif
ifdef __UNIX__
    xor eax,eax
else
    SetEnvironmentVariable(string, rbx)
endif
    .if ( rbx )
        mov TCHAR ptr [rbx-TCHAR],'='
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
