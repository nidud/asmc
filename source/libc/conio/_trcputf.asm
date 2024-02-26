; _TRCPUTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc
include tchar.inc

    .code

_rcputf proc rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, attrib:WORD, format:LPTSTR, argptr:vararg

    _vstprintf( &_bufin, format, &argptr )
    _rcputs( rc, p, x, y, attrib, &_bufin )
    ret

_rcputf endp

    end
