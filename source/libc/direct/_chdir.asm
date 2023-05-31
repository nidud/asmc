; _CHDIR.ASM--
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
    .code

_chdir proc directory:LPSTR

    ldr rcx,directory

ifdef __UNIX__

    .ifsd ( sys_chdir(rcx) < 0 )

        neg eax
        _set_errno(eax)
        .return(-1)
    .endif
else
    .new abspath[_MAX_PATH]:char_t
    .new result[4]:char_t

    .ifd SetCurrentDirectoryA( rcx )

        .ifd GetCurrentDirectoryA( _MAX_PATH, &abspath )

            .if ( abspath[1] != ':' )
                .return( 0 )
            .endif

            mov al,abspath[0]
            .if ( al >= 'a' && al <= 'z' )
                sub al,'a' - 'A'
            .endif

            mov result[0],'='
            mov result[1],al
            mov result[2],':'
            mov result[3],0
            .ifd SetEnvironmentVariableA( &result, &abspath )
                .return( 0 )
            .endif
        .endif
    .endif
    _dosmaperr( GetLastError() )
endif
    ret

_chdir endp

    end
