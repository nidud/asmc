; _TSETFATTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
ifndef __UNIX__
include winbase.inc
endif
include errno.inc
include tchar.inc

    .code

_tsetfattr proc file:LPTSTR, attrib:UINT
ifdef __UNIX__
    mov eax,-1
else
    .ifd ( SetFileAttributes( ldr(file), ldr(attrib) ) == 0 )

        .return( _dosmaperr( GetLastError() ) )
    .endif
    xor eax,eax
endif
    ret

_tsetfattr endp

    end

