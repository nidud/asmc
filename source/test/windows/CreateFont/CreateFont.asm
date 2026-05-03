;
; https://msdn.microsoft.com/en-us/library/windows/desktop/dd183499(v=vs.85).aspx
;
include windows.inc
include tchar.inc

.code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    local wmId, wmEvent
    local ps:PAINTSTRUCT
    local hdc:HDC
    local rect:RECT
    local hBrush:HBRUSH
    local hFont:HFONT

    .switch message

      .case WM_PAINT

        mov hdc,BeginPaint(hWnd, &ps)

        ; Logical units are device dependent pixels, so this will create a
        ; handle to a logical font that is 48 pixels in height.
        ; The width, when set to 0, will cause the font mapper to choose the
        ; closest matching value. The font face name will be Impact.

        mov hFont,CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, "Impact")
        SelectObject(hdc, hFont)

        ; Sets the coordinates for the rectangle in which the text is to be formatted.
        SetRect(&rect, 100,100,700,200)
        SetTextColor(hdc, RGB(255,0,0))
        DrawText(hdc, "Drawing Text with Impact", -1, &rect, DT_NOCLIP)


        ; Logical units are device dependent pixels, so this will create a
        ; handle to a logical font that is 36 pixels in height.
        ; The width, when set to 20, will cause the font mapper to choose a font
        ; which, in this case, is stretched.
        ; The font face name will be Times New Roman.  This time nEscapement is
        ; at -300 tenths of a degree (-30 degrees)
        mov hFont, CreateFont(36,20,-300,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH, "Times New Roman")
        SelectObject(hdc, hFont)

        ; Sets the coordinates for the rectangle in which the text is to be formatted.
        SetRect(&rect, 100, 200, 900, 800);
        SetTextColor(hdc, RGB(0,128,0));
        DrawText(hdc, "Drawing Text with Times New Roman", -1, &rect, DT_NOCLIP)

        ; Logical units are device dependent pixels, so this will create a handle
        ; to a logical font that is 36 pixels in height.
        ; The width, when set to 10, will cause the font mapper to choose a font
        ; which, in this case, is compressed.
        ; The font face name will be Arial. This time nEscapement is at 250
        ; tenths of a degree (25 degrees)

        mov hFont,CreateFont(36,10,250,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,VARIABLE_PITCH,
            "Arial")
        SelectObject(hdc,hFont)

        ; Sets the coordinates for the rectangle in which the text is to be formatted.
        SetRect(&rect, 500, 200, 1400, 600)
        SetTextColor(hdc, RGB(0,0,255))
        DrawText(hdc, "Drawing Text with Arial", -1, &rect, DT_NOCLIP)
        DeleteObject(hFont)

        EndPaint(hWnd, &ps)
        xor eax,eax
        .endc

      .case WM_DESTROY
        PostQuitMessage(0)
        xor eax,eax
        .endc
      .default
        DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    ret
    endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,&WndProc
    mov wc.cbClsExtra,0
    mov wc.cbWndExtra,0
    mov wc.hInstance,hInstance
    mov wc.hbrBackground,COLOR_WINDOW+1
    mov wc.lpszMenuName,NULL
    mov wc.lpszClassName,&@CStr("WndClass")
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)

    RegisterClassEx(&wc)
    mov eax,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "WndClass", "Window", WS_OVERLAPPEDWINDOW,
        eax, eax, eax, eax, 0, 0, hInstance, 0)
    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)
    .while GetMessage(&msg, 0, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    mov rax,msg.wParam
    ret
    endp

    end _tstart
