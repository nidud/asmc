; _PRINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    option win64:rsp

_print proc format:LPSTR, arglist:VARARG
    _write(1, addr _bufin, ftobufin(format, addr arglist))
    ret
_print endp

    END
