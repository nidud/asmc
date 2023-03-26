; _SCPUTFA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_scputfA proc x:BYTE, y:BYTE, format:LPSTR, argptr:vararg

    vsprintf( &_bufin, format, &argptr )
    _scputsA( x, y, &_bufin )
    ret

_scputfA endp

    end
