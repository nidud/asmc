; _TGETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winbase.inc
include errno.inc
include tchar.inc

    .code

ifdef _UNICODE
_tgetfattr proc lpFilename:LPTSTR
else
_tgetfattr proc uses rbx lpFilename:LPTSTR
endif

ifdef __UNIX__

    _set_errno( ENOSYS )
    mov rax,-1

elseifdef _UNICODE

    ldr rcx,lpFilename

    .ifd ( GetFileAttributes( rcx ) == -1 )

        _dosmaperr( GetLastError() )
    .endif

else

   .new wpath:wstring_t
    ldr rbx,lpFilename

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

