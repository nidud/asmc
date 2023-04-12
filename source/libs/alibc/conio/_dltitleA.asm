; _DLTITLEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:THWND

_dltitleA proc uses rbx hwnd:THWND, string:LPSTR

   .new rc:TRECT = { 0, 0, 1, 1 }

    mov rbx,rdi
    mov rc.col,[rbx].rc.col

    _rcclear(rc, [rbx].window, _getattrib(BG_TITLE, FG_TITLE))

    _rccenterA([rbx].rc, [rbx].window, rc, 0, string)
    ret

_dltitleA endp

    end
