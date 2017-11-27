include stdio.inc
include io.inc

    .code

_print proc C format:LPSTR, arglist:VARARG

    _write(1, &_bufin, ftobufin(format, &arglist))
    ret

_print endp

    END
