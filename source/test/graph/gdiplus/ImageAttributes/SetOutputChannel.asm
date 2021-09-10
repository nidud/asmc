;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-setoutputchannel
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
       .new image:Image(L"Mosaic.png")
       .new width:UINT
       .new height:UINT
       .new w:UINT
       .new h:UINT

        mov width,image.GetWidth()
        add eax,20
        mov w,eax
        mov height,image.GetHeight()
        add eax,20
        mov h,eax

        ;; Draw the image unaltered.
        g.DrawImage(&image, 10, 10, width, height)

       .new imAtt:ImageAttributes()

       .new r1:Rect(10, h, width, height)
        imul r8d,h,2
        sub r8d,10
       .new r2:Rect(10, r8d, width, height)
       .new r3:Rect(w, 10, width, height)
       .new r4:Rect(w, h, width, height)

        ;; Draw the image, showing the intensity of the cyan channel.
        imAtt.SetOutputChannel(ColorChannelFlagsC, ColorAdjustTypeBitmap)
        g.DrawImage(&image, &r1, 0, 0, width, height, UnitPixel, &imAtt)

        ;; Draw the image, showing the intensity of the magenta channel.
        imAtt.SetOutputChannel(ColorChannelFlagsM, ColorAdjustTypeBitmap)
        g.DrawImage(&image, &r2, 0, 0, width, height, UnitPixel, &imAtt)

        ;; Draw the image, showing the intensity of the yellow channel.
        imAtt.SetOutputChannel(ColorChannelFlagsY, ColorAdjustTypeBitmap)
        g.DrawImage(&image, &r3, 0, 0, width, height, UnitPixel, &imAtt)

        ;; Draw the image, showing the intensity of the black channel.
        imAtt.SetOutputChannel(ColorChannelFlagsK, ColorAdjustTypeBitmap)
        g.DrawImage(&image, &r4, 0, 0, width, height, UnitPixel, &imAtt)

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
                100, 80, 300, 400, NULL, NULL, hInstance, 0)

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

