; _TENVPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .data
    _tenvptr tstring_t 0

    .code

ifndef __UNIX__

__initenvptr proc private
    mov _tenvptr,_tgetenvs()
    ret
__initenvptr endp

.pragma init(__initenvptr, 4)

endif

    end
