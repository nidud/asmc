;
; https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-metafiles-about
;

include windows.inc
include gdiplus.inc
include tchar.inc

    .code

WndProc proc uses rbx hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

       .new m:Metafile(L"MyDiskFile.emf", ps.hdc)
       .new g:Graphics(&m)

        g.SetSmoothingMode(SmoothingModeAntiAlias)
        g.RotateTransform(30.0)

       .new p:GraphicsPath()

        p.AddEllipse(0, 0, 200, 100)

       .new r:Region(&p)

        g.SetClip(&r)

       .new b:Pen(Blue)

        g.DrawPath(&b, &p)

        .for ebx = 0: ebx <= 300: ebx += 10

            mov eax,300
            sub eax,ebx
            g.DrawLine(&b, 0, 0, eax, ebx)
        .endf

        g.Release()
        m.Release()
        EndPaint(hWnd, &ps)
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
    mov wc.hbrBackground,   COLOR_ACTIVEBORDER
    mov wc.lpszMenuName,    rax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.hInstance,       rcx
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("Metafile")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Metafile", "gdiplus.Graphics(Create Metafile)", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 600,400, NULL, NULL, hInstance, 0)

            mov hwnd,rax

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

