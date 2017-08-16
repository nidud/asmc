;
; https://msdn.microsoft.com/en-us/library/windows/desktop/dd183499(v=vs.85).aspx
; https://msdn.microsoft.com/en-us/library/windows/desktop/hh298375(v=vs.85).aspx
;
include windows.inc

ifdef _UNICODE
MSFTEDIT_CLASS equ <L"RICHEDIT50W">
else
MSFTEDIT_CLASS equ <"RICHEDIT50W">
endif

.data
hEdit HWND ?

.code

CreateRichEdit proc hwndOwner:HWND, ; Dialog box handle.
                    x:SINT, y:SINT, ; Location.
                    w:SINT, h:SINT, ; Dimensions.
                    hinst:HINSTANCE ; Application or DLL instance.

    LoadLibrary("Msftedit.dll")
    CreateWindowEx(0, MSFTEDIT_CLASS, "Type here",
        ES_MULTILINE or WS_VISIBLE or WS_CHILD or WS_BORDER or WS_TABSTOP,
        x, y, w, h,
        hwndOwner, NULL, hinst, NULL)
    ret

CreateRichEdit endp

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

        ; Get the font face from Rich Edit handle.

        mov hFont,SendMessage(hEdit, WM_GETFONT, 0, 0)
        SelectObject(hdc, hFont)

        SetRect(&rect, 10,120,500,100)
        SetTextColor(hdc, RGB(255,0,0))
        DrawText(hdc, "Drawing Text with Rich Edit font", -1, &rect, DT_NOCLIP)

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
WndProc endp

WinMain proc WINAPI hInstance: HINSTANCE,
     hPrevInstance: HINSTANCE,
         lpCmdLine: LPSTR,
          nShowCmd: SINT

    local wc:WNDCLASSEX
    local msg:MSG
    local hwnd:HANDLE

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,WndProc

    mov ecx,hInstance
    xor eax,eax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov wc.hInstance,ecx
    mov wc.hbrBackground,COLOR_WINDOW+1
    mov wc.lpszMenuName,eax

    lea eax,@CStr("WndClass")
    mov wc.lpszClassName,eax
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,eax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)

    RegisterClassEx(&wc)

    mov eax,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "WndClass", "Window", WS_OVERLAPPEDWINDOW,
        eax, eax, eax, eax, 0, 0, hInstance, 0)

    mov hEdit,CreateRichEdit(eax, 10, 10, 500, 100, hInstance)

    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)

    .while GetMessage(&msg, 0, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    mov eax,msg.wParam
    ret

WinMain endp

ifdef __PE__
WinStart proc
    mov ebx,GetModuleHandle(0)
    ExitProcess(WinMain(ebx, 0, GetCommandLineA(), SW_SHOWDEFAULT))
WinStart endp
else
WinStart equ <>
endif
    end WinStart
