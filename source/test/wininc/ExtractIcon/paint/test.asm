include windows.inc
include tchar.inc

    .data
    regedit TCHAR @CatStr(<!">, @Environ(SystemRoot),<!">),"\regedit.exe",0
    dz      TCHAR @CatStr(<!">, @Environ(AsmcDir),<!">),"\bin\dz.exe",0

    .code

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

  local ps:PAINTSTRUCT, hDC:HDC, hIcon:HICON

    .switch message

      .case WM_PAINT
        mov hDC,BeginPaint(hWnd, &ps)

        .if ExtractIcon(hWnd, &regedit, 0)

            mov hIcon,rax
            DrawIcon(hDC, 100, 75, rax)
            DestroyIcon(hIcon)
        .endif

        .if ExtractIcon(hWnd, &dz, 0)

            mov hIcon,rax
            DrawIcon(hDC, 200, 75, rax)
            DestroyIcon(hIcon)
        .endif

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

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local wc:WNDCLASSEX, msg:MSG, hwnd:HANDLE

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    lea rax,WndProc
    mov wc.lpfnWndProc,rax
    mov rcx,hInstance
    xor eax,eax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov wc.hInstance,rcx
    mov wc.hbrBackground,COLOR_WINDOW+1
    mov wc.lpszMenuName,rax
    lea rax,@CStr("WndClass")
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)
    RegisterClassEx(&wc)

    mov ecx,CW_USEDEFAULT
    mov hwnd,CreateWindowEx(0, "WndClass", "Window", WS_OVERLAPPEDWINDOW,
        ecx, ecx, ecx, ecx, 0, 0, hInstance, 0)
    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)

    .while GetMessage(&msg, 0, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    mov rax,msg.wParam
    ret

_tWinMain endp

    end _tstart
