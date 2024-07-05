
WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch message

    .case WM_PAINT

        BeginPaint(hWnd, &ps)
        OnPaint(ps.hdc, &ps)
        EndPaint(hWnd, &ps)
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if word ptr wParam == VK_ESCAPE
        .endc
    .default
        .return DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    .return( 0 )

WndProc endp

ifndef WINWIDTH
define WINWIDTH 600
endif
ifndef WINHEIGHT
define WINHEIGHT 400
endif

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      0
    mov wc.cbWndExtra,      0
    mov wc.hbrBackground,   COLOR_ACTIVEBORDER
    mov wc.lpszMenuName,    NULL
    mov wc.hIcon,           NULL
    mov wc.hIconSm,         NULL
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr(CLASSNAME)
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, CLASSNAME, "gdiplus.Graphics(" CLASSNAME ")", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, WINWIDTH , WINHEIGHT, NULL, NULL, hInstance, 0)

            mov hwnd,rax
ifdef __HWND__
            mov g_hwnd,rax
endif
           ;; Initialize GDI+.
           .new gdiplus:GdiPlus()

            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)
            .while GetMessage(&msg, 0, 0, 0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
            gdiplus.Release()
            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart
