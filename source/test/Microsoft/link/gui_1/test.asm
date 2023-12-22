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
       .new G:Graphics(rax)
       .new P:GraphicsPath()

        P.AddEllipse(200, 0, 200, 200)

       .new B:PathGradientBrush(&P)

        mov count,1

        B.SetCenterColor(ColorAlpha(Green, 180))
        mov FullTranslucent,ColorAlpha(Black, 230)
        B.SetSurroundColors(&FullTranslucent, &count)
        G.SetSmoothingMode(SmoothingModeAntiAlias)
        G.FillEllipse(&B, 200 + 2, 0 + 2, 200 - 4, 200 - 4)
        B.Release()
        P.Release()

       .new P:GraphicsPath()

        P.AddEllipse(200, 100, 150, 150)

       .new B:PathGradientBrush(&P)

        B.SetCenterColor(ColorAlpha(Yellow, 180))
        mov FullTranslucent,ColorAlpha(Red, 200)
        B.SetSurroundColors(&FullTranslucent, &count)
        G.FillEllipse(&B, 200 + 2, 100 + 2, 150 - 4, 150 - 4)
        B.Release()
        P.Release()
        G.Release()
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

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    .new wc:WNDCLASSEX = {
        WNDCLASSEX,                     ; .cbSize
        CS_HREDRAW or CS_VREDRAW,       ; .style
        &WndProc,                       ; .lpfnWndProc
        0,                              ; .cbClsExtra
        0,                              ; .cbWndExtra
        hInstance,                      ; .hInstance
        LoadIcon(NULL, IDI_APPLICATION),; .hIcon
        LoadCursor(NULL, IDC_ARROW),    ; .hCursor
        GetStockObject(BLACK_BRUSH),    ; .hbrBackground
        NULL,                           ; .lpszMenuName
        "Sphere",                       ; .lpszClassName
        wc.hIcon                        ; .hIconSm
        }

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Sphere", "gdiplus.Graphics(Sphere)", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, hInstance, 0)

           .new hwnd:HANDLE = rax
           .new gdiplus:GdiPlus() ; Initialize GDI+.

            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)

            .new msg:MSG
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

wWinMainCRTStartup proc

    ExitProcess(wWinMain(GetModuleHandle(0), 0, 0, SW_SHOWDEFAULT))

wWinMainCRTStartup endp

    end
