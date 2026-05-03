include windows.inc
include tchar.inc

    .code

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    local hdc:HDC
    local ps:PAINTSTRUCT

    .switch message
    .case WM_PAINT

        .new hWhitePen:HPEN
        .new hOldPen:HPEN

        mov hdc,BeginPaint(hWnd, &ps)
        MoveToEx(hdc, 50, 50, NULL)
        LineTo(hdc, 250, 50)
        mov hWhitePen,GetStockObject(WHITE_PEN)
        mov hOldPen,SelectObject(hdc, hWhitePen)
        MoveToEx(hdc, 50, 100, NULL)
        LineTo(hdc, 250, 100)
        SelectObject(hdc, hOldPen)
        EndPaint(hWnd, &ps)
        .endc
    .case WM_CHAR
        .endc .if dword ptr wParam != VK_ESCAPE
    .case WM_DESTROY
        PostQuitMessage(0)
        .return 0
    .endsw
    .return DefWindowProc(hWnd, message, wParam, lParam)

WndProc endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.lpszMenuName,    rax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.hbrBackground,   GetSysColorBrush(COLOR_3DFACE)
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("Lines")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Lines", "Lines", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 300, 200, NULL, NULL, hInstance, NULL)

            mov hwnd,rax

            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)
            .while GetMessage(&msg, 0, 0, 0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw

            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart

