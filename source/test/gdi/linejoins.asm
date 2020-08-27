include windows.inc
include tchar.inc

    .code

DoDrawing proc hwnd:HWND

    local brush:LOGBRUSH
    local col:COLORREF
    local pen_style:DWORD

    mov col,RGB(0, 0, 0)
    mov pen_style,PS_SOLID or PS_JOIN_MITER or PS_GEOMETRIC

    mov brush.lbStyle,BS_SOLID
    mov brush.lbColor,col
    mov brush.lbHatch,0

    .new ps:PAINTSTRUCT
    .new hdc:HDC

    mov hdc,BeginPaint(hwnd, &ps)

    .new hPen1:HPEN
    .new holdPen:HPEN

    mov hPen1,ExtCreatePen(pen_style, 8, &brush, 0, NULL)
    mov holdPen,SelectObject(hdc, hPen1)

    .new points[5]:POINT

    mov points[0x00].x,30
    mov points[0x00].y,30
    mov points[0x08].x,130
    mov points[0x08].y,30
    mov points[0x10].x,130
    mov points[0x10].y,100
    mov points[0x18].x,30
    mov points[0x18].y,100
    mov points[0x20].x,30
    mov points[0x20].y,30

    Polygon(hdc, &points, 5)

    mov pen_style,PS_SOLID or PS_GEOMETRIC or PS_JOIN_BEVEL

    .new hPen2:HPEN
    mov hPen2,ExtCreatePen(pen_style, 8, &brush, 0, NULL)

    SelectObject(hdc, hPen2)
    DeleteObject(hPen1)

    .new points2[5]:POINT

    mov points2[0x00].x,160
    mov points2[0x00].y,30
    mov points2[0x08].x,260
    mov points2[0x08].y,30
    mov points2[0x10].x,260
    mov points2[0x10].y,100
    mov points2[0x18].x,160
    mov points2[0x18].y,100
    mov points2[0x20].x,160
    mov points2[0x20].y,30

    MoveToEx(hdc, 130, 30, NULL)
    Polygon(hdc, &points2, 5)

    mov pen_style,PS_SOLID or PS_GEOMETRIC or PS_JOIN_ROUND
    .new hPen3:HPEN
    mov hPen3,ExtCreatePen(pen_style, 8, &brush, 0, NULL)

    SelectObject(hdc, hPen3)
    DeleteObject(hPen2)

    .new points3[5]:POINT

    mov points3[0x00].x,290
    mov points3[0x00].y,30
    mov points3[0x08].x,390
    mov points3[0x08].y,30
    mov points3[0x10].x,390
    mov points3[0x10].y,100
    mov points3[0x18].x,290
    mov points3[0x18].y,100
    mov points3[0x20].x,290
    mov points3[0x20].y,30

    MoveToEx(hdc, 260, 30, NULL)
    Polygon(hdc, &points3, 5)

    SelectObject(hdc, holdPen)
    DeleteObject(hPen3)
    EndPaint(hwnd, &ps)
    ret

DoDrawing endp

WndProc proc WINAPI hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local hdc:HDC
  local ps:PAINTSTRUCT

    .switch message
    .case WM_PAINT
        DoDrawing(hWnd)
        .endc
    .case WM_CHAR
        .endc .if dword ptr wParam != VK_ESCAPE
    .case WM_DESTROY
        PostQuitMessage(0)
        .return 0
    .endsw
    .return DefWindowProc(hWnd, message, wParam, lParam)

WndProc endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.lpszMenuName,    rax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.hbrBackground,   GetStockObject(WHITE_BRUSH)
    mov wc.hInstance,       hInstance
    mov wc.lpfnWndProc,     &WndProc
    mov wc.lpszClassName,   &@CStr(L"Pens")
    mov wc.hCursor,         LoadCursor(0, IDC_ARROW)

    .ifd RegisterClassEx(&wc)

        .if CreateWindowEx(0, wc.lpszClassName, L"Linejoins", WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100, 100, 450, 200, NULL, NULL, hInstance, NULL)

            .while GetMessage(&msg, 0, 0, 0)
                TranslateMessage(&msg)
                DispatchMessage(&msg)
            .endw
            mov rax,msg.wParam
        .endif
    .endif
    ret

_tWinMain endp

    end _tstart
