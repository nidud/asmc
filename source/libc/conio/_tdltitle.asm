; _TDLTITLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:THWND

_dltitle proc uses rbx hwnd:THWND, string:LPTSTR

    mov rbx,hwnd
   .new rc:TRECT = { 0, 0, [rbx].rc.col, 1}
    _at BG_TITLE,FG_TITLE,' '
    _rcclear(rc, [rbx].window, eax)
    _rccenter([rbx].rc, [rbx].window, rc, 0, string)
    ret

_dltitle endp

    end
