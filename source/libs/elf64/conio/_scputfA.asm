; _SCPUTFA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_scputfA proc _x:BYTE, _y:BYTE, format:LPSTR, argptr:vararg

   .new x:BYTE = _x
   .new y:BYTE = _y

    mov r10,format
    vsprintf( &_bufin, r10, rax )
    _scputsA( x, y, &_bufin )
    ret

_scputfA endp

    end
