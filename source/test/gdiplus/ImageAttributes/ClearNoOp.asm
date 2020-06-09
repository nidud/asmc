;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-clearnoop
;

include windows.inc
include gdiplus.inc
include tchar.inc

    .data
     brushMatrix ColorMatrix {{    ;; red converted to green
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 1.0
        }}
    .code

WndProc proc uses rsi rdi hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

       .new g:Graphics(rax)
       .new i:Image(L"TestMetafile4.emf")
       .new imAtt:ImageAttributes()

        mov esi,i.GetWidth()
        mov edi,i.GetHeight()

       .new r1:Rect(0,   0, esi, edi)
       .new r2:Rect(0,  80, esi, edi)
       .new r3:Rect(0, 160, esi, edi)

        imAtt.SetColorMatrix(&brushMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeBrush)

        ;; Draw the image (metafile) using brush color adjustment.
        ;; Items filled with a brush change from red to green.
        g.DrawImage(&i, &r1, 0, 0, esi, edi, UnitPixel, &imAtt)

        ;; Temporarily disable brush color adjustment.
        imAtt.SetNoOp(ColorAdjustTypeBrush)

        ;; Draw the image (metafile) without brush color adjustment.
        ;; There is no change from red to green.
        g.DrawImage(&i, &r2, 0, 0, esi, edi, UnitPixel, &imAtt)

        ;; Reinstate brush color adjustment.
        imAtt.ClearNoOp(ColorAdjustTypeBrush)

        ;; Draw the image (metafile) using brush color adjustment.
        ;; Items filled with a brush change from red to green.
        g.DrawImage(&i, &r3, 0, 0, esi, edi, UnitPixel, &imAtt)

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
    mov wc.lpszClassName,   &@CStr("ClearBrushRemapTable")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, "ClearBrushRemapTable", "ClearBrushRemapTable", WS_OVERLAPPEDWINDOW,
                100, 80, 420, 380, NULL, NULL, hInstance, 0)

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

