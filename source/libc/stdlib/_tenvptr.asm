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

init_envptr proc private
    mov _tenvptr,_tgetenvs()
    ret
init_envptr endp

.pragma init(init_envptr, 4)

endif

    end
