;
; http://masm32.com/board/index.php?topic=5929.msg65018#msg65018
;
include windows.inc

	.win64: rbp
	.code

start proc

    mov rbx,GetModuleHandle(0)
    ExitProcess(WinMain(rbx, 0, GetCommandLine(), SW_SHOWDEFAULT))

start endp

WinMain PROC hInstance: HINSTANCE,
	 hPrevInstance: HINSTANCE,
	     lpCmdLine: LPSTR,
	      nShowCmd: SINT

    LOCAL   wc:WNDCLASSEX
    LOCAL   msg:MSG
    LOCAL   hwnd:HANDLE

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    mov rax,OFFSET WndProc
    mov wc.lpfnWndProc,rax

    xor rax,rax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov wc.hInstance,rcx
    mov wc.hbrBackground,COLOR_WINDOW+1
    mov wc.lpszMenuName,rax

    lea rax,@CStr("WndClass")
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0,IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0,IDC_ARROW)

    RegisterClassEx(ADDR wc)

    mov eax,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0,"WndClass","Window",WS_OVERLAPPEDWINDOW,
		eax,eax,eax,eax,0,0,hInstance,0)

    ShowWindow(hwnd,SW_SHOWNORMAL)
    UpdateWindow(hwnd)

    .while GetMessage(ADDR msg,0,0,0)

	TranslateMessage(ADDR msg)
	DispatchMessage(ADDR msg)
    .endw

    mov rax,msg.wParam
    ret

WinMain ENDP

	.win64: rsp nosave

WndProc PROC hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .if edx == WM_DESTROY

	PostQuitMessage(0)
	xor rax,rax
    .else
	DefWindowProc(rcx, edx, r8, r9)
    .endif
    ret

WndProc ENDP

    END
