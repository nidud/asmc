;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-getadjustedpalette
;

include windows.inc
include gdiplus.inc
include tchar.inc

    .code

WndProc proc uses rsi hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

       .new g:Graphics(rax)

       ;; Create a palette that has four entries.

       .new p:ptr ColorPalette(4)
        mov rcx,rax
        [rcx].ColorPalette.SetPalette(0, Aqua)
        [rcx].ColorPalette.SetPalette(1, White)
        [rcx].ColorPalette.SetPalette(2, Red)
        [rcx].ColorPalette.SetPalette(3, Green)

        ;; Display the four palette colors with no adjustment.

       .new b:SolidBrush(Black)

        .for (esi = 0: esi < 4: ++esi)

            p.GetPalette(rsi)
            b.SetColor(eax)

            imul r8d,esi,30
            add  r8d,20

            g.FillRectangle(&b, r8d, 20, 20, 20)
        .endf

        ;; Create a remap table that converts green to blue.

       .new map:ColorMap
        mov map.oldColor,Green
        mov map.newColor,Blue

        ;; Create an ImageAttributes object, and set its bitmap remap table.

       .new imAtt:ImageAttributes()

        imAtt.SetRemapTable(1, &map, ColorAdjustTypeBitmap)

        ;; Adjust the palette.

        imAtt.GetAdjustedPalette(p, ColorAdjustTypeBitmap)

        ;; Display the four palette colors after the adjustment.

        .for (esi = 0: esi < 4: ++esi)

            p.GetPalette(rsi)
            b.SetColor(eax)

            imul r8d,esi,30
            add  r8d,20

            g.FillRectangle(&b, r8d, 50, 20, 20)
        .endf

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
    mov wc.hbrBackground,   COLOR_ACTIVEBORDER
    mov wc.lpszMenuName,    rax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.hInstance,       rcx
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("GetAdjustedPalette")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "GetAdjustedPalette", "GetAdjustedPalette", WS_OVERLAPPEDWINDOW,
                100, 80, 400, 160, NULL, NULL, hInstance, 0)

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

