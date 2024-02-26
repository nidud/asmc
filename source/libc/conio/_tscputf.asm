; _TSCPUTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc
include tchar.inc

    .code

_scputf proc x:BYTE, y:BYTE, format:LPTSTR, argptr:vararg

    _vstprintf( &_bufin, format, &argptr )
    _scputs( x, y, &_bufin )
    ret

_scputf endp

    end
