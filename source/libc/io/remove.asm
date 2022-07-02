; REMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

    .code

remove proc file:LPSTR

    .if DeleteFileA( file )

        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret

remove endp

    end
