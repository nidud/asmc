;
; http://masm32.com/board/index.php?topic=5929.msg65018#msg65018
;
include windows.inc

    .code

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .if edx == WM_DESTROY
	PostQuitMessage(0)
	xor rax,rax
    .else
	DefWindowProc(rcx, edx, r8, r9)
    .endif
    ret

WndProc endp

WinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    xor eax,eax
    mov wc.cbSize,	    WNDCLASSEX
    mov wc.style,	    CS_HREDRAW or CS_VREDRAW
    mov wc.cbClsExtra,	    eax
    mov wc.cbWndExtra,	    eax
    mov wc.hInstance,	    rcx
    mov wc.hbrBackground,   COLOR_WINDOW+1
    mov wc.lpszMenuName,    rax
    mov wc.lpszClassName,   &@CStr("WndClass")
    mov wc.lpfnWndProc,	    &WndProc
    mov wc.hIcon,	    LoadIcon(0,IDI_APPLICATION)
    mov wc.hIconSm,	    rax
    mov wc.hCursor,	    LoadCursor(0,IDC_ARROW)

    RegisterClassEx(&wc)
    mov ecx,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0,"WndClass","Window",WS_OVERLAPPEDWINDOW,
		ecx,ecx,ecx,ecx,0,0,hInstance,0)
    ShowWindow(hwnd,SW_SHOWNORMAL)
    UpdateWindow(hwnd)
    .while GetMessage(&msg,0,0,0)
	TranslateMessage(&msg)
	DispatchMessage(&msg)
    .endw
    mov rax,msg.wParam
    ret

WinMain endp

    end
