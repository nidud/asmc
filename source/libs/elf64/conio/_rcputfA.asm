; _RCPUTFA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_rcputfA proc _rc:TRECT, _p:PCHAR_INFO, _x:BYTE, _y:BYTE, _attrib:WORD, format:LPSTR, argptr:vararg

   .new rc:TRECT        = _rc
   .new p:PCHAR_INFO    = _p
   .new x:BYTE          = _x
   .new y:BYTE          = _y
   .new attrib:WORD     = _attrib

    vsprintf( &_bufin, format, rax )
    _rcputsA( rc, p, x, y, attrib, &_bufin )
    ret

_rcputfA endp

    end
