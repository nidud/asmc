;
; https://docs.microsoft.com/en-us/windows/win32/api/gdiplusimageattributes/nf-gdiplusimageattributes-imageattributes-clearbrushremaptable
;
include windows.inc
include gdiplus.inc
include tchar.inc

    .code

WndProc proc uses rsi rdi hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT

    .switch edx

    .case WM_PAINT

        BeginPaint(rcx, &ps)

       .new g:Graphics(rax)
       .new i:Image(L"TestMetafile4.emf")
       .new imAtt:ImageAttributes()
       .new defaultMap:ColorMap
       .new brushMap:ColorMap

        mov defaultMap.oldColor,MakeARGB(255, 255, 0, 0)   ;; red converted to blue
        mov defaultMap.newColor,MakeARGB(255, 0, 0, 255)   ;;
        mov brushMap.oldColor,MakeARGB(255, 255, 0, 0)     ;; red converted to green
        mov brushMap.newColor,MakeARGB(255, 0, 255, 0)     ;;

        ;; Set the default color-remap table.
        imAtt.SetRemapTable(1, &defaultMap, ColorAdjustTypeDefault)

        mov esi,i.GetWidth()
        mov edi,i.GetHeight()

        .new r1:Rect( 0,   0, esi, edi)
        .new r2:Rect(10,  90, esi, edi)
        .new r3:Rect(10, 170, esi, edi)
        .new r4:Rect(10, 250, esi, edi)

        ;; Draw the image (metafile) using no color adjustment.
        g.DrawImage(&i, &r1, 0, 0, esi, edi, UnitPixel)

        ;; Draw the image (metafile) using default color adjustment.
        ;; All red is converted to blue.
        g.DrawImage(&i, &r2, 0, 0, esi, edi, UnitPixel, &imAtt)

        ;; Set the brush remap table.
        imAtt.SetBrushRemapTable(1, &brushMap)

        ;; Draw the image (metafile) using default and brush adjustment.
        ;; Red painted with a brush is converted to green.
        ;; All other red is converted to blue (default).
        g.DrawImage(&i,  &r3, 0, 0, esi, edi, UnitPixel, &imAtt)

        ;; Clear the brush remap table.
        imAtt.ClearBrushRemapTable()

        ;; Draw the image (metafile) using only default color adjustment.
        ;; Red painted with a brush gets no color adjustment.
        ;; All other red is converted to blue (default).
        g.DrawImage(&i, &r4, 0, 0, esi, edi, UnitPixel, &imAtt)

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
                100, 80, 420, 460, NULL, NULL, hInstance, 0)

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

