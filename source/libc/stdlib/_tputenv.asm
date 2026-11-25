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

ifndef _UNICODE
undef putenv
ALIAS <putenv>=<_putenv>
endif

.code

_tputenv proc uses rbx string:tstring_t
   .new value:tstring_t = NULL
   .new namebuf[256]:tchar_t
    ldr rbx,string
    .if ( !rbx || byte ptr [rbx] == 0 )
        .return( _set_errno( EINVAL ) )
    .endif
    .if ( _tcschr(rbx, '=') != NULL )
        mov rcx,rax
        add rax,tchar_t
        mov value,rax
        sub rcx,rbx
        mov namebuf[rcx],0
        mov rbx,memcpy(&namebuf, rbx, rcx)
    .endif
    .ifd !SetEnvironmentVariable(rbx, value)
        dec rax
       .return
    .endif
ifdef __UNIX__
    xor eax,eax
else
    .if ( _tgetenvs() )
        mov rbx,_tenvptr
        mov _tenvptr,rax
        .if ( _tsetenvp( &value ) )
            free(rbx)
            free(_tenviron)
            mov _tenviron,value
            xor eax,eax
        .else
            free(_tenvptr)
            mov _tenvptr,rbx
            mov eax,-1
        .endif
    .else
        dec rax
    .endif
endif
    ret
    endp

    end
