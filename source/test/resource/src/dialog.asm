include windows.inc
include tchar.inc
include res/dialog.inc

define IDR_MYDIALOG 100
define CLASSNAME <"MyWindowDialog">

.code

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .switch ldr(uMsg)
    .case WM_CLOSE
    .case WM_COMMAND
        EndDialog(hWnd, 0)
       .return TRUE
    .endsw
    .return FALSE
    endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance: HINSTANCE, lpCmdLine: LPTSTR, nCmdShow: SINT
    DialogBox(hInstance, MAKEINTRESOURCE(IDR_MYDIALOG), NULL, &WndProc)
    .return( 0 )
    endp

    end _tstart
