include windows.inc
include gdiplus.inc
include tchar.inc

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch edx

    .case WM_PAINT

        .new ps:PAINTSTRUCT

        BeginPaint(rcx, &ps)

        .new g:Graphics(rax)
        .new rc:PointF

        .new Person:GraphicsPath()
        .new p:Pen(Blue)

        Person.AddEllipseI(23, 1, 14, 14)
        Person.AddLineI(18, 16, 42, 16)
        Person.AddLineI(50, 40, 44, 42)
        Person.AddLineI(38, 25, 37, 42)
        Person.AddLineI(45, 75, 37, 75)
        Person.AddLineI(30, 50, 23, 75)
        Person.AddLineI(16, 75, 23, 42)
        Person.AddLineI(22, 25, 16, 42)
        Person.AddLineI(10, 40, 18, 16)

        g.ScaleTransform(4.0, 4.0)
        g.DrawPath(&p, &Person)
        g.ResetTransform()

        p.Release()
        Person.Release()
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
    mov wc.hbrBackground,   COLOR_WINDOW+1
    mov wc.lpszMenuName,    rax
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("Person")
    mov wc.hIcon,           LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,         rax
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Person", "gdiplus.Graphics(Person)", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 600,400, NULL, NULL, hInstance, 0)

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
