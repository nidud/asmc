include windows.inc
include time.inc
include tchar.inc

    .code

DrawPixels proc hwnd:HWND

  local ps:PAINTSTRUCT
  local r:RECT
  local hdc:HDC
  local i:int_t, x:int_t, y:int_t

    GetClientRect(hwnd, &r)

    .return .if (r.bottom == 0)

    mov hdc,BeginPaint(hwnd, &ps)

    .for (i=0: i<1000: i++)

        rand()
        xor edx,edx
        div r.right
        mov x,edx
        rand()
        xor edx,edx
        div r.bottom
        mov y,edx

        SetPixel(hdc, x, y, RGB(255, 0, 0))
    .endf

    EndPaint(hwnd, &ps)
    ret

DrawPixels endp

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch message
    .case WM_PAINT
        DrawPixels(hWnd)
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
    mov wc.lpszClassName,   &@CStr("Pixels")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Pixels", "Pixels", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 300, 250, NULL, NULL, hInstance, NULL)

            mov hwnd,rax

            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)
            .while GetMessage(&msg, 0, 0, 0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw

            srand(time(NULL))

            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart

