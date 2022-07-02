; _FINDCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

    .code

_findclose proc handle:intptr_t

    .if !FindClose( handle )

        _dosmaperr( GetLastError() )
    .else
        xor eax,eax
    .endif
    ret

_findclose endp

    end
