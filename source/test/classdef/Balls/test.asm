WIN32_LEAN_AND_MEAN equ 1
include windows.inc
include Balls.inc

.data
hwnd        HANDLE 0
g           LPGRAPHICS 0
EventStop   UINT 0
speed       UINT 5

.code

ThrdProc proc uses rsi rdi rbx

  local hdc:HDC

    mov hdc,GetDC(hwnd)
    mov rsi,g
    assume rsi:LPGRAPHICS

    .while !EventStop

        .while [rsi].flags & _G_SUSPENDED

            Sleep(2)
        .endw

        .if [rsi].flags & _G_UPDATE

            mov edi,[rsi].Getmaxx()
            mov ebx,[rsi].Getmaxy()
            and [rsi].flags,not _G_UPDATE
            SetDIBitsToDevice(hdc, 0, 0, edi, ebx, 0, 0, 0, ebx, [rsi].winptr, &[rsi].bmi, DIB_RGB_COLORS)
        .else
            [rsi].Moveballs()
            or [rsi].flags,_G_UPDATE
            Sleep(speed)
        .endif

    .endw
    assume rsi:nothing
    ReleaseDC(hwnd, hdc)
    ret

ThrdProc endp

WndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .repeat

        .switch rdx

        .case WM_SIZE
            .endc .if r8d == SIZE_MINIMIZED
            g.Suspend()
            mov r8,lParam
            movzx edx,r8w
            shr r8d,16
            g.Setsize(edx, r8d)
            g.Resume()
            .endc

        .case WM_KEYDOWN
            .switch r8d
              .case VK_SPACE
                .endc
              .case VK_RETURN
                g.Suspend()
                g.Hideballs()
                g.Initballs()
                g.Resume()
                .endc
              .case VK_ESCAPE
                .gotosw1(WM_CLOSE)
              .case VK_F1
                .gotosw1(WM_RBUTTONDOWN)
              .case VK_UP
                mov speed,0
                .endc
              .case VK_DOWN
                mov speed,6
                .endc
              .case VK_RIGHT
                .endc
            .endsw
            .endc

        .case WM_RBUTTONDOWN
            MessageBox(hWnd,
                "Up:\tFast.\n"
                "Down:\tSlow.\n"
                "Enter:\tReset.\n"
                "Escape:\tExit the program.",
                "Asmc-OOP: Balls", MB_OK)
            .endc

        .case WM_LBUTTONDOWN
            .endc

        .case WM_CLOSE
        .case WM_DESTROY
            mov EventStop,1
            Sleep(10)
            PostQuitMessage(0)
            .endc

        .default
            DefWindowProc( rcx, edx, r8, r9 )
            .break
        .endsw
        xor eax,eax
    .until 1
    ret

WndProc endp

WinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPSTR, nShowCmd:SINT

  local wc:WNDCLASSEX
  local msg:MSG
  local idThread:UINT
  local rc:RECT

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW or CS_BYTEALIGNCLIENT
    lea rax,WndProc
    mov wc.lpfnWndProc,rax

    xor rax,rax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov wc.hInstance,rcx
    mov wc.hbrBackground,COLOR_MENUTEXT
    mov wc.lpszMenuName,rax

    lea rax,@CStr("WndClass")
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0, 500)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)

    .repeat

        .break .ifd !RegisterClassEx( &wc )
        .break .if !CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, "WndClass", "Asmc-OOP: Balls",
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, 0 )

        mov hwnd,rax
        GetClientRect( hwnd, &rc )
        Graphics::Graphics( &g )
        ShowWindow(hwnd, SW_SHOWNORMAL)
        UpdateWindow(hwnd)
        CreateThread(NULL, NULL, &ThrdProc, NULL, NORMAL_PRIORITY_CLASS, &idThread)
        CloseHandle(rax)

        .while GetMessage(&msg,0,0,0)

            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .endw
        mov rax,msg.wParam
    .until 1
    ret

WinMain endp

    end
