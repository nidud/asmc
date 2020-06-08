;
; https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-metafiles-about
;
include windows.inc
include gdiplus.inc
include tchar.inc

    .data
    MetafileCreated BOOL FALSE

    .code

CreateMetafile proc uses rbx hdc:HDC

   .new m:Metafile(L"MyDiskFile.emf", hdc)
   .new g:Graphics(&m)
   .new p:GraphicsPath()
   .new b:Pen(Red)

    g.SetSmoothingMode(SmoothingModeAntiAlias)
    g.RotateTransform(30.0)
    p.AddEllipse(0, 0, 200, 100)

   .new r:Region(&p)

    g.SetClip(&r)
    g.DrawPath(&b, &p)

    .for ebx = 0: ebx <= 300: ebx += 10

        mov eax,300
        sub eax,ebx
        g.DrawLine(&b, 0, 0, eax, ebx)
    .endf
    p.Release()
    b.Release()
    g.Release()
    m.Release()
    mov MetafileCreated,TRUE
    ret

CreateMetafile endp

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

        .if MetafileCreated == FALSE

            CreateMetafile(rax)
            mov rax,ps.hdc
        .endif

       .new g:Graphics(rax)
       .new i:Image(L"MyDiskFile.emf")

        g.DrawImage(&i, 10, 10)

        i.Release()
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
    mov wc.hbrBackground,   COLOR_ACTIVEBORDER
    mov wc.lpszMenuName,    rax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.hInstance,       rcx
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("Metafile2")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "Metafile2", "gdiplus.Graphics(View Metafile)", WS_OVERLAPPEDWINDOW,
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

