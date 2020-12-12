include windows.inc

.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local hdc:HDC
  local ps:PAINTSTRUCT

    .switch message
    .case WM_PAINT
        mov hdc,BeginPaint(hWnd, &ps)
        Rectangle(hdc, 50, 50, 200, 100)
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

WinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG

    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      0
    mov wc.cbWndExtra,      0
    mov wc.lpszMenuName,    NULL
    mov wc.hIcon,           NULL
    mov wc.hIconSm,         NULL
    mov wc.hbrBackground,   GetSysColorBrush(COLOR_3DFACE)
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("Rectangle")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Rectangle", "Rectangle", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 250, 200, NULL, NULL, hInstance, NULL)

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
