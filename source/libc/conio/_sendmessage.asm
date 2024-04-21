; _SENDMESSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:THWND

_sendmessage proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr rbx,hwnd
    .if ( [rbx].flags & W_WNDPROC && [rbx].flags & W_CHILD )

        .return( [rbx].winproc(rbx, uiMsg, wParam, lParam) )
    .endif
    .if ( [rbx].flags & O_CHILD )

        .if _dlgetfocus(rbx)

            mov rbx,rax
            .if ( [rbx].flags & W_WNDPROC )
                .return .ifd ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
            .endif
            mov rbx,hwnd
        .endif
        .for ( rbx = [rbx].object : rbx : )
            .if ( [rbx].flags & W_WNDPROC )
                .return .ifd ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
            .endif
            mov rbx,[rbx].next
        .endf
        mov rbx,hwnd
    .endif
    .for ( eax = 1 : rbx : )

        .if ( [rbx].flags & W_WNDPROC )
            .break .ifd ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
        .endif
        mov rbx,[rbx].prev
    .endf
    ret

_sendmessage endp

    end
