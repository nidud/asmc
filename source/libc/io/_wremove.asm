; _WREMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

.code

_wremove proc file:LPWSTR
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov eax,-1
else
    .if DeleteFileW( file )

        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
endif
    ret

_wremove endp

    end
