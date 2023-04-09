; _RCPUTFW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_rcputfW proc rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, attrib:WORD, format:LPWSTR, argptr:vararg

    vswprintf( &_bufin, format, &argptr )
    _rcputsW( rc, p, x, y, attrib, &_bufin )
    ret

_rcputfW endp

    end
