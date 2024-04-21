; _TMSGBOX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include tchar.inc

    .code

_msgbox proc flags:UINT, title:LPTSTR, format:LPTSTR, argptr:vararg

    _vstprintf(&_bufin, format, &argptr)
    _vmsgbox(flags, title, &_bufin)
    ret

_msgbox endp

    end
