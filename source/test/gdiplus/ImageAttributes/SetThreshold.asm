;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-setoutputchannelcolorprofile
;

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
       .new w:UINT
       .new h:UINT

        ;; Create an Image object based on a .bmp file.
        ;; The image has one stripe with RGB components (160, 0, 0)
        ;; and one stripe with RGB components (0, 140, 0).

       .new image:Image(L"RedGreenThreshold.png")

       ;; Create an ImageAttributes object, and set its bitmap threshold to 0.6

       .new imAtt:ImageAttributes()
        imAtt.SetThreshold(0.6, ColorAdjustTypeBitmap)

        mov w,image.GetWidth()
        mov h,image.GetHeight()

        ;; Draw the image with no color adjustment.
        g.DrawImage(&image, 10, 10, w, h)

       .new rc:Rect(100, 10, w, h)

        ;; Draw the image with the threshold applied.
        ;; 160 > 0.6*255, so the red stripe will be changed to full intensity.
        ;; 140 < 0.6*255, so the green stripe will be changed to zero intensity.

        g.DrawImage(&image, &rc, 0, 0, w, h, UnitPixel, &imAtt)

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
    mov wc.lpszClassName,   &@CStr("SetThreshold")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "SetThreshold", "SetThreshold", WS_OVERLAPPEDWINDOW,
                100, 80, 400, 200, NULL, NULL, hInstance, 0)

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

