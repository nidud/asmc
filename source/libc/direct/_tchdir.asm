; _TCHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
ifdef __UNIX__
include linux/kernel.inc
else
include winbase.inc
endif
include tchar.inc

    .code

_tchdir proc directory:LPTSTR

    ldr rcx,directory

ifdef __UNIX__
ifdef _UNICODE
    _set_errno( ENOSYS )
    mov eax,-1
else
    .ifsd ( sys_chdir(rcx) < 0 )

        neg eax
        _set_errno(eax)
        mov rax,-1
    .endif
endif
else
    .new abspath[_MAX_PATH]:TCHAR
    .new result[4]:TCHAR

    .ifd SetCurrentDirectory( rcx )

        .ifd GetCurrentDirectory( _MAX_PATH, &abspath )

            .if ( abspath[TCHAR] != ':' )
                .return( 0 )
            .endif

            movzx eax,abspath[0]
            .if ( eax >= 'a' && eax <= 'z' )
                sub eax,'a' - 'A'
            .endif

            mov result[0],'='
ifdef _UNICODE
            mov result[TCHAR],ax
else
            mov result[TCHAR],al
endif
            mov result[TCHAR*2],':'
            mov result[TCHAR*3],0
            .ifd SetEnvironmentVariable( &result, &abspath )
                .return( 0 )
            .endif
        .endif
    .endif
    _dosmaperr( GetLastError() )
endif
    ret

_tchdir endp

    end
