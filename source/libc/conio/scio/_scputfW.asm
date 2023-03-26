; _SCPUTFW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_scputfW proc x:BYTE, y:BYTE, format:LPWSTR, argptr:vararg

    vswprintf( &_bufin, format, &argptr )
    _scputsW( x, y, &_bufin )
    ret

_scputfW endp

    end
