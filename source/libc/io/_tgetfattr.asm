; _TGETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdlib.inc
ifdef __UNIX__
include sys/stat.inc
else
include winbase.inc
endif
include errno.inc
include tchar.inc

    .code

if defined(_UNICODE) or defined(__UNIX__)
_tgetfattr proc lpFilename:LPTSTR
    ldr rcx,lpFilename
ifdef __UNIX__
    .new s:_stat32
    .ifd ( _stat(rcx, &s) == 0 )

        mov eax,s.st_mode
    .endif
else
    .ifd ( GetFileAttributes( rcx ) == -1 )

        _dosmaperr( GetLastError() )
    .endif
endif
else
_tgetfattr proc uses rbx lpFilename:LPTSTR
    ldr rbx,lpFilename

    .new wpath:wstring_t
    .ifd ( GetFileAttributes( rbx ) == -1 )

        .ifd ( _pathtow( rbx, &wpath ) == true )

            mov ebx,GetFileAttributesW( wpath )
            free( wpath )
           .return( ebx )
        .endif
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_tgetfattr endp

    end

