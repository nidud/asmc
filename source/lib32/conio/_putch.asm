; _PUTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include io.inc

    .code

_putch proc char

    _write(2, &char, 1)
    ret

_putch endp

    END
