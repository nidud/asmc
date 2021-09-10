include windows.inc

.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch message
    .case WM_PAINT
       .new ps:PAINTSTRUCT
       .new hdc:HDC = BeginPaint(hWnd, &ps)
        Rectangle(hdc, 50, 50, 200, 100)
        EndPaint(hWnd, &ps)
       .return 0
    .case WM_CHAR
       .endc .if dword ptr wParam != VK_ESCAPE
    .case WM_DESTROY
        PostQuitMessage(0)
       .return 0
    .endsw
    .return DefWindowProc(hWnd, message, wParam, lParam)

WndProc endp

WinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WndProc,                       ; .lpfnWndProc
        0,                              ; .cbClsExtra
        0,                              ; .cbWndExtra
        hInstance,                      ; .hInstance
        NULL,                           ; .hIcon
        LoadCursor(NULL, IDC_ARROW),    ; .hCursor
        GetSysColorBrush(COLOR_3DFACE), ; .hbrBackground
        NULL,                           ; .lpszMenuName
        "Rectangle",                    ; .lpszClassName
        NULL                            ; .hIconSm
        }

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Rectangle", "Rectangle",
                WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 250, 200, NULL, NULL, hInstance, NULL)

            .new msg:MSG
            .while GetMessage(&msg, 0, 0, 0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
            .return msg.wParam
        .endif
    .endif
    ret

WinMain endp

    end
