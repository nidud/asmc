; _TERRMSG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include tchar.inc

    .code

_errmsg proc title:tstring_t, format:tstring_t, argptr:vararg

    _vstprintf(&_bufin, format, &argptr)
    _vmsgbox(MB_OK or MB_ICONERROR, title, &_bufin)
    ret

_errmsg endp

    end
