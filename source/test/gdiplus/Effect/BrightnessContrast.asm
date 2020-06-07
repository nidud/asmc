
include windows.inc
include gdiplus.inc
include tchar.inc

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

       .new g:Graphics(rax)
       .new i:Image(L"Photograph.jpg")
       .new r:RectF
       .new m:Matrix(1.0, 0.0, 0.0, 1.0, 20.0, 280.0)
       .new P:BrightnessContrastParams
       .new B:BrightnessContrast()

        mov r.X,0.0
        mov r.Y,0.0
        i.GetWidth()
        cvtsi2ss xmm0,eax
        movss r.Width,xmm0
        i.GetHeight()
        cvtsi2ss xmm0,eax
        movss r.Height,xmm0

        ;; Integer in the range -255 through 255 that specifies the brightness
        ;; level. If the value is 0, the brightness remains the same. As the
        ;; value moves from 0 to 255, the brightness of the image increases. As
        ;; the value moves from 0 to -255, the brightness of the image decreases.
        mov P.brightnessLevel,-80
        ;; Integer in the range -100 through 100 that specifies the contrast
        ;; level. If the value is 0, the contrast remains the same. As the value
        ;; moves from 0 to 100, the contrast of the image increases. As the
        ;; value moves from 0 to -100, the contrast of the image
        mov P.contrastLevel,-10
        B.SetParameters(&P)

        ;; Draw the image with no change.
        g.DrawImage(&i, 20.0, 20.0, r.Width, r.Height)

        ;; Draw the image with applied Effect
        g.DrawImage(&i, &r, &m, &B, NULL, UnitPixel)

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
    mov wc.lpszClassName,   &@CStr("EffectSharpen")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "EffectSharpen", "EffectSharpen", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 460, 600, NULL, NULL, hInstance, 0)

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

