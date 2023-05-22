; _CONIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include fcntl.inc
include conio.inc

    .data
     _conin int_t -1

    .code

__initconin proc private

    mov _conin,_open(CONIN, O_BINARY or O_RDWR or O_NOCTTY)
    ret

__initconin endp

.pragma init(__initconin, 20)

    end
