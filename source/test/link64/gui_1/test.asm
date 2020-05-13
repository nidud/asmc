include windows.inc
include gdiplus.inc

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch edx

    .case WM_PAINT

       .new ps:PAINTSTRUCT

        BeginPaint(rcx, &ps)

       .new count:SINT
       .new FullTranslucent:ARGB
       .new G:Graphics()

        .if G.FromHDC2(ps.hdc, rax) == Ok

           .new P:GraphicsPath()
           .new B:PathGradientBrush()

            mov count,1

            P.CreatePath(FillModeAlternate)
            B.CreateFromPath(&P)
            P.AddPathEllipseI(200, 0, 200, 200)
            B.SetCenterColor(ColorAlpha(Green, 180))
            mov FullTranslucent,ColorAlpha(Black, 230)
            B.SetSurroundColors(&FullTranslucent, &count)
            G.SetSmoothingMode(SmoothingModeAntiAlias)
            G.FillEllipseI(&B, 200 + 2, 0 + 2, 200 - 4, 200 - 4)
            B.Release()
            P.Release()

            P.CreatePath(FillModeAlternate)
            P.AddPathEllipseI(200, 100, 150, 150)
            B.CreateFromPath(&P)
            B.SetCenterColor(ColorAlpha(Yellow, 180))
            mov FullTranslucent,ColorAlpha(Red, 200)
            B.SetSurroundColors(&FullTranslucent, &count)
            G.FillEllipseI(&B, 200 + 2, 100 + 2, 150 - 4, 150 - 4)
            B.Release()
            P.Release()
        .endif
        G.Release()
        EndPaint(hWnd, &ps)
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .endc
    .default
        .return DefWindowProc(rcx, edx, r8, r9)
    .endsw
    xor eax,eax
    ret

WndProc endp

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hbrBackground,   COLOR_WINDOW+1
    mov wc.lpszMenuName,    rax
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("Sphere")
    mov wc.hIcon,           LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,         rax
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Sphere", "gdiplus.Graphics(Sphere)", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, 0)

            mov hwnd,rax

            ;; Initialize GDI+.
            .new gdiplus:ptr GdiPlus()

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

wWinMain endp

wWinStart proc frame uses rbx

    mov rbx,GetModuleHandle(0)
    ExitProcess(wWinMain(rbx, 0, GetCommandLineW(), SW_SHOWDEFAULT))

wWinStart endp

    end wWinStart
