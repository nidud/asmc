include windows.inc
include tchar.inc

    .code

DrawLines proc hwnd:HWND

  local ps:PAINTSTRUCT
  local hdc:HDC
  local hPen1:HPEN
  local hPen2:HPEN
  local hPen3:HPEN
  local hPen4:HPEN
  local hPen5:HPEN
  local holdPen:HPEN

    mov hdc,BeginPaint(hwnd, &ps)
    mov hPen1,CreatePen(PS_SOLID, 1, RGB(0, 0, 0))
    mov hPen2,CreatePen(PS_DASH, 1, RGB(0, 0, 0))
    mov hPen3,CreatePen(PS_DOT, 1, RGB(0, 0, 0))
    mov hPen4,CreatePen(PS_DASHDOT, 1, RGB(0, 0, 0))
    mov hPen5,CreatePen(PS_DASHDOTDOT, 1, RGB(0, 0, 0))

    mov holdPen,SelectObject(hdc, hPen1)

    MoveToEx(hdc, 50, 30, NULL)
    LineTo(hdc, 300, 30)

    SelectObject(hdc, hPen2)
    MoveToEx(hdc, 50, 50, NULL)
    LineTo(hdc, 300, 50)

    SelectObject(hdc, hPen2)
    MoveToEx(hdc, 50, 70, NULL)
    LineTo(hdc, 300, 70)

    SelectObject(hdc, hPen3)
    MoveToEx(hdc, 50, 90, NULL)
    LineTo(hdc, 300, 90)

    SelectObject(hdc, hPen4)
    MoveToEx(hdc, 50, 110, NULL)
    LineTo(hdc, 300, 110)

    SelectObject(hdc, holdPen)
    DeleteObject(hPen1)
    DeleteObject(hPen2)
    DeleteObject(hPen3)
    DeleteObject(hPen4)
    DeleteObject(hPen5)

    EndPaint(hwnd, &ps)
    ret

DrawLines endp

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local hdc:HDC
  local ps:PAINTSTRUCT

    .switch message
    .case WM_PAINT
        DrawLines(hWnd)
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
    mov wc.lpszClassName,   &@CStr("Penstyles")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Penstyles", "Penstyles", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 350, 180, NULL, NULL, hInstance, NULL)

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

