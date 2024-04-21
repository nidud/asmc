; _TERRMSG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include tchar.inc

    .code

_stdmsg proc title:LPTSTR, format:LPTSTR, argptr:vararg

    _vstprintf(&_bufin, format, &argptr)
    _vmsgbox(MB_OK, title, &_bufin)
    ret

_stdmsg endp

    end
