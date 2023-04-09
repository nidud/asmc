; _SCPUTFA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc

    .code

_scputfA proc x:BYTE, y:BYTE, format:LPSTR, argptr:vararg

    mov r10,rdx
    vsprintf( &_bufin, r10, rax )
    _scputsA( x, y, &_bufin )
    ret

_scputfA endp

    end
