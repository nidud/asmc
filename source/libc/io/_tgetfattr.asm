; _TGETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc
include errno.inc
include tchar.inc

.code

_tgetfattr proc file:tstring_t
    .ifd ( GetFileAttributes( ldr(file) ) == -1 )
        _dosmaperr( GetLastError() )
    .endif
    ret
    endp

    end

