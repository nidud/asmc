; _TCONTROL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; A text control is added externally (Unicode/ASCII) and buffering
; added to the main window (128*TCHAR+TEDIT)
;
; Flags:
;
; O_DEXIT   - dialog exits on Enter
; O_USEBEEP - if no-can-do: try to delete a char at the end
; O_SELECT  - text is auto selected on entry
;
include conio.inc
include tchar.inc

    .code

    assume rbx:THWND

WndProc proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov rbx,hwnd
    .switch uiMsg
    .case WM_CREATE
        _tcontrol([rbx].object, 128, "string to edit")
        _dlshow(rbx)
        _dlsetfocus(rbx, 0)
        .return( 0 )
    .case WM_CLOSE
        _dlclose(rbx)
        .return( 0 )
    .endsw
    .return(_defwinproc(hwnd, uiMsg, wParam, lParam))

WndProc endp

_tmain proc argc:int_t, argv:array_t

   .new rc:TRECT = { 10, 8, 50, 8 }
   .new ec:TRECT = { 15, 3, 20, 1 }

    mov rbx,_dlopen(rc, 1, W_MOVEABLE or W_TRANSPARENT or W_SHADE, 128*TCHAR+TEDIT)
    _dltitle(rbx, "Text Control")
    _dlinit (rbx, 0, ec, O_DEXIT or O_USEBEEP or O_SELECT, T_EDIT, 1, 0)
    _dlmodal(rbx, &WndProc)
    ret

_tmain endp

    end
