include windows.inc
include gdiplus.inc
include tchar.inc

    .data
    hBitmap HBITMAP 0

    .code

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch message
    .case WM_CREATE
       .new gdiplus:GdiPlus()
       .new bitmap:Bitmap(L"..\\res\\image.png")
        bitmap.GetHBITMAP(0, &hBitmap)
        bitmap.Release()
        gdiplus.Release()
       .endc
    .case WM_PAINT
       .new ps:PAINTSTRUCT
       .new hdc:HDC = BeginPaint(hWnd, &ps)
       .new hMemDC:HANDLE = CreateCompatibleDC(hdc)
       .new bm:BITMAP
        SelectObject(hMemDC, hBitmap)
        GetObject(hBitmap, BITMAP, &bm)
        BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY)
        DeleteDC(hMemDC)
        EndPaint(hWnd, &ps)
       .endc
    .case WM_DESTROY
        DeleteObject(hBitmap)
        PostQuitMessage(0)
       .endc
    .case WM_CHAR
       .gotosw(WM_DESTROY) .if word ptr wParam == VK_ESCAPE
       .endc
    .default
       .return DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    .return 0

WndProc endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      0
    mov wc.cbWndExtra,      0
    mov wc.hbrBackground,   COLOR_ACTIVEBORDER
    mov wc.lpszMenuName,    NULL
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr("BitmapClass")
    mov wc.hIcon,           LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,         NULL
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)
        .if CreateWindowEx(0, "BitmapClass", "Bitmap from file", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, 0)
            mov hwnd,rax
            ShowWindow(hwnd, SW_SHOWNORMAL)
            UpdateWindow(hwnd)
            .while GetMessage(&msg,0,0,0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart
