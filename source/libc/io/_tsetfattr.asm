; _TSETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc
include errno.inc
include tchar.inc

.code

_tsetfattr proc file:tstring_t, attrib:uint_t
    .ifd ( SetFileAttributes( ldr(file), ldr(attrib) ) == 0 )
        .return( _dosmaperr( GetLastError() ) )
    .endif
    xor eax,eax
    ret
    endp

    end

