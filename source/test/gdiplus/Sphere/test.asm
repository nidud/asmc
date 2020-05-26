include windows.inc
include gdiplus.inc
include tchar.inc

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch edx

    .case WM_PAINT

       .new ps:PAINTSTRUCT
       .new count:SINT
       .new FullTranslucent:ARGB

        BeginPaint(rcx, &ps)

       .new g:Graphics(rax)

        ; Create a GraphicsPath object
       .new p:GraphicsPath()

        ; Add an ellipse to the path
        p.AddEllipseI(200, 0, 200, 200)

        ; Create a path gradient based on the ellipse
       .new b:PathGradientBrush(&p)

        ; Set the middle color of the path
        b.SetCenterColor(ColorAlpha(Green, 180))

        ; Set the entire path boundary to Alpha Black using translucency
        mov count,1
        mov FullTranslucent,ColorAlpha(Black, 230)
        b.SetSurroundColors(&FullTranslucent, &count)

        ; Draw the ellipse, keeping the exact coords we defined for the path
        ; We use AntiAlias drawing mode.
        ; To get a better antialising we enlarge area (+2 and -4).
        g.SetSmoothingMode(SmoothingModeAntiAlias)
        g.FillEllipseI(&b, 200 + 2, 0 + 2, 200 - 4, 200 - 4)

        b.Release()
        p.Release()

        ; Second Sphere

       .new p:GraphicsPath()

        p.AddEllipseI(200, 100, 150, 150)

       .new b:PathGradientBrush(&p)

        b.SetCenterColor(ColorAlpha(Yellow, 180))
        mov FullTranslucent,ColorAlpha(Red, 200)
        mov count,1
        b.SetSurroundColors(&FullTranslucent, &count)
        g.FillEllipseI(&b, 200 + 2, 100 + 2, 150 - 4, 150 - 4)

        b.Release()
        p.Release()
        g.Release()
        EndPaint(hWnd, &ps)
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if r8d == VK_ESCAPE
        .endc
    .default
        .return DefWindowProc(rcx, edx, r8, r9)
    .endsw
    xor eax,eax
    ret

WndProc endp

_tWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hbrBackground,   COLOR_WINDOW
    mov wc.lpszMenuName,    rax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("Sphere")

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Sphere", "gdiplus.Graphics(Sphere)", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, 0)

            mov hwnd,rax

            ;; Initialize GDI+.
            .new gdiplus:GdiPlus()

            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)

            .while GetMessage(&msg,0,0,0)
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
