include windows.inc
include tchar.inc

    .code

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    local hdc:HDC
    local ps:PAINTSTRUCT
    local points[4]:POINT

    mov points[0x00].x,20
    mov points[0x00].y,40
    mov points[0x08].x,320
    mov points[0x08].y,200
    mov points[0x10].x,330
    mov points[0x10].y,110
    mov points[0x18].x,450
    mov points[0x18].y,40

    .switch message
    .case WM_PAINT
        mov hdc,BeginPaint(hWnd, &ps)
        PolyBezier(hdc, &points, 4)
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
    mov wc.lpszClassName,   &@CStr("Beziercurve")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Beziercurve", "Beziercurve", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 500, 200, NULL, NULL, hInstance, NULL)

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

