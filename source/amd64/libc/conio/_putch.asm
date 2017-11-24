include conio.inc
include io.inc

.code

_putch proc char
    _write(2, &char, 1)
    ret
_putch endp

    end
