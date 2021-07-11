; _SCPUTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_scputf proc x:int_t, y:int_t, format:string_t, argptr:vararg

    vsprintf(&_bufin, format, &argptr)
    _scputs(x, y, &_bufin)
    ret

_scputf endp

    END
