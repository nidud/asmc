include stdio.inc
include io.inc

    .code

    option win64:rsp

_print proc format:LPSTR, arglist:VARARG
    _write(1, addr _bufin, ftobufin(format, addr arglist))
    ret
_print endp

    END
