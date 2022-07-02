; _WCHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include winbase.inc

    .code

_wchdir proc directory:LPWSTR

    .new abspath[_MAX_PATH]:wchar_t
    .new result[4]:wchar_t

    .ifd SetCurrentDirectoryW( directory )

        .ifd GetCurrentDirectoryW( _MAX_PATH, &abspath )

            .if ( abspath[2] != ':' )
                .return( 0 )
            .endif

            mov ax,abspath[0]
            .if ( ax >= 'a' && ax <= 'z' )
                sub ax,'a' - 'A'
            .endif

            mov result[0],'='
            mov result[2],ax
            mov result[4],':'
            mov result[6],0
            .ifd SetEnvironmentVariableW( &result, &abspath )
                .return( 0 )
            .endif
        .endif
    .endif
    _dosmaperr( GetLastError() )
    ret

_wchdir endp

    end
