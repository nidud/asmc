; _TDLMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include conio.inc

    .code

    assume rbx:THWND

_dlmodal proc uses rbx hwnd:THWND, wndp:TPROC
    ldr rbx,hwnd
    mov [rbx].winproc,wndp
    or  [rbx].flags,W_WNDPROC
    [rbx].winproc(rbx, WM_CREATE, 0, 0)
    _dlsetfocus(rbx, [rbx].index)
    .new modein:int_t = -1
    .ifd GetConsoleMode(_coninpfh, &modein)
        .ifd SetConsoleMode(_coninpfh, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
            FlushConsoleInputBuffer(_coninpfh)
        .endif
    .endif
    .new msg:MESSAGE
    .whiled _getmessage(&msg, NULL, 1)
        .return .if ( eax == -1 )
        _translatemsg(&msg)
        _dispatchmsg(&msg)
    .endw
    .if ( modein != -1 )
        SetConsoleMode(_coninpfh, modein)
    .endif
    _sendmessage(rbx, WM_CLOSE, msg.wParam, msg.lParam)
    .return( msg.wParam )
    endp

    end
