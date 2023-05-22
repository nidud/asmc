; _CONOUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include fcntl.inc
include conio.inc

    .data
     _conout int_t -1

    .code

__initconout proc private

    mov _conout,_open(CONOUT, O_BINARY or O_RDWR or O_NOCTTY)
    ret

__initconout endp

.pragma init(__initconout, 21)

    end
