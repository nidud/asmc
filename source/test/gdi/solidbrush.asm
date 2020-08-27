include windows.inc
include tchar.inc

    .code

DrawRectangles proc hwnd:HWND

    local ps:PAINTSTRUCT
    local hdc:HDC

    mov hdc,BeginPaint(hwnd, &ps)

    .new hPen:HPEN
    .new holdPen:HPEN

    mov hPen,CreatePen(PS_NULL, 1, RGB(0, 0, 0))
    mov holdPen,SelectObject(hdc, hPen)

    .new hBrush1:HBRUSH
    .new hBrush2:HBRUSH
    .new hBrush3:HBRUSH
    .new hBrush4:HBRUSH
    .new holdBrush:HBRUSH

    mov hBrush1,CreateSolidBrush(RGB(121, 90, 0))
    mov hBrush2,CreateSolidBrush(RGB(240, 63, 19))
    mov hBrush3,CreateSolidBrush(RGB(240, 210, 18))
    mov hBrush4,CreateSolidBrush(RGB(9, 189, 21))

    mov holdBrush,SelectObject(hdc, hBrush1)

    Rectangle(hdc, 30, 30, 100, 100)
    SelectObject(hdc, hBrush2)
    Rectangle(hdc, 110, 30, 180, 100)
    SelectObject(hdc, hBrush3)
    Rectangle(hdc, 30, 110, 100, 180)
    SelectObject(hdc, hBrush4)
    Rectangle(hdc, 110, 110, 180, 180)

    SelectObject(hdc, holdPen)
    SelectObject(hdc, holdBrush)

    DeleteObject(hPen)
    DeleteObject(hBrush1)
    DeleteObject(hBrush2)
    DeleteObject(hBrush3)
    DeleteObject(hBrush4)
    EndPaint(hwnd, &ps)
    ret

DrawRectangles endp

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local hdc:HDC
  local ps:PAINTSTRUCT

    .switch message
    .case WM_PAINT
        DrawRectangles(hWnd)
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

  local wc:WNDCLASSEX, msg:MSG

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
    mov wc.lpszClassName,   &@CStr(L"Brush")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, wc.lpszClassName, L"Solid Brush", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 220, 240, NULL, NULL, hInstance, NULL)

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
