; _RCPUTFA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_rcputfA proc rc:TRECT, p:PCHAR_INFO, x:SINT, y:SINT, attrib:WORD, format:LPSTR, argptr:vararg

    vsprintf( &_bufin, format, &argptr )
    _rcputsA( rc, p, x, y, attrib, &_bufin )
    ret

_rcputfA endp

    end
