;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-getadjustedpalette
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

        ;; Create an Image object based on a BMP file.
        ;; The image has three horizontal stripes.
        ;; The color of the top stripe has RGB components (90, 90, 20).
        ;; The color of the middle stripe has RGB components (150, 150, 150).
        ;; The color of the bottom stripe has RGB components (130, 130, 40).

       .new image:Image(L"ColorKeyTest.png")

        ;; Create an ImageAttributes object, and set its color key.

       .new imAtt:ImageAttributes()
       .new c1:Color(100, 95, 30)
       .new c2:Color(250, 245, 60)

        imAtt.SetColorKey(c1, c2, ColorAdjustTypeBitmap)

        ;; Draw the image. Apply the color key.
        ;; The bottom stripe of the image will be transparent because
        ;; 100 <= 130 <= 250 and
        ;; 95  <= 130 <= 245 and
        ;; 30  <= 40  <= 60.

       .new w:int_t
       .new h:int_t

        mov w,image.GetWidth()
        mov h,image.GetHeight()

       .new r:Rect(20, 20, w, h)

        g.DrawImage(&image, &r, 0, 0, w, h, UnitPixel, &imAtt)

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
    mov wc.lpszClassName,   &@CStr("SetColorKey")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "SetColorKey", "SetColorKey", WS_OVERLAPPEDWINDOW,
                100, 80, 400, 300, NULL, NULL, hInstance, 0)

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

