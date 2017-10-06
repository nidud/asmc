;
; http://win32assembly.programminghorizon.com/tut16.html
;
include windows.inc
include winres.inc
ifdef _WIN64
option win64:3
APPNAME   equ <"Win64 ASM Event Example">
CLASSNAME equ <"Win64ASMEventClass">
else
rax equ <eax>
rbx equ <ebx>
rcx equ <ecx>
APPNAME   equ <"Win32 ASM Event Example">
CLASSNAME equ <"Win32ASMEventClass">
endif

IDM_START_THREAD    equ 1
IDM_STOP_THREAD     equ 2
IDM_EXIT            equ 3
IDR_MAINMENU        equ 30
WM_FINISH           equ WM_USER+100h

.data
EventStop   BOOL FALSE
hMenu       HANDLE ?
hwnd        HANDLE ?
hEventStart HANDLE ?
hThread     HANDLE ?
ThreadID    dd ?

.code

ThrdProc proc

    .while 1

        WaitForSingleObject(hEventStart, INFINITE)

        mov ecx,600000000

        .while ecx

            .if EventStop != TRUE

                add eax,eax
                dec ecx
            .else

                MessageBox(hwnd, "The thread is stopped",
                        "The calculation is completed!", MB_OK)

                mov EventStop,FALSE
                .continue(1)
            .endif
        .endw

        PostMessage(hwnd, WM_FINISH, 0, 0)
        EnableMenuItem(hMenu, IDM_START_THREAD, MF_ENABLED)
        EnableMenuItem(hMenu, IDM_STOP_THREAD, MF_GRAYED)
    .endw
    ret

ThrdProc endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch uMsg

      .case WM_DESTROY
        PostQuitMessage(NULL)
        xor eax,eax
        .endc

      .case WM_COMMAND

        .if !lParam ; menu commands

            movzx eax,word ptr wParam
            .switch eax

              .case IDM_START_THREAD
                SetEvent(hEventStart)
                EnableMenuItem(hMenu, IDM_START_THREAD, MF_GRAYED)
                EnableMenuItem(hMenu, IDM_STOP_THREAD, MF_ENABLED)
                .endc

              .case IDM_STOP_THREAD
                mov EventStop,TRUE
                EnableMenuItem(hMenu, IDM_START_THREAD, MF_ENABLED)
                EnableMenuItem(hMenu, IDM_STOP_THREAD, MF_GRAYED)
                .endc

              .case IDM_EXIT
                DestroyWindow(hWnd)
                .endc
            .endsw
        .endif
        xor eax,eax
        .endc

      .case WM_CREATE
        mov hEventStart,CreateEvent(NULL, FALSE, FALSE, NULL)
        mov hThread,CreateThread(NULL, NULL, &ThrdProc, NULL, NORMAL_PRIORITY_CLASS, &ThreadID)
        CloseHandle(hThread)
        xor eax,eax
        .endc

      .case WM_FINISH
        MessageBox(0, "The calculation is completed!", APPNAME, MB_OK)
        xor eax,eax
        .endc

      .default
        DefWindowProc(hWnd, uMsg, wParam, lParam)
    .endsw
    ret

WndProc endp

WinMain proc WINAPI hInst: HINSTANCE,
     hPrevInstance: HINSTANCE,
         lpCmdLine: LPSTR,
          nShowCmd: SINT

    local wc:WNDCLASSEX
    local msg:MSG

    mov wc.cbSize,SIZEOF WNDCLASSEX
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    mov wc.lpfnWndProc,WndProc
    mov rcx,hInst
    xor eax,eax
    mov wc.cbClsExtra,eax
    mov wc.cbWndExtra,eax
    mov wc.hInstance,rcx
    mov wc.hbrBackground,COLOR_WINDOW
    mov wc.lpszMenuName,IDR_MAINMENU
ifdef _WIN64
    lea rax,@CStr("Win64ASMEventClass")
else
    lea rax,@CStr("Win32ASMEventClass")
endif
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)
    RegisterClassEx(&wc)

    mov hwnd,CreateWindowEx(WS_EX_CLIENTEDGE, CLASSNAME,
        APPNAME, WS_OVERLAPPEDWINDOW or WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, 0, 0, hInst, 0)

    ShowWindow(hwnd, SW_SHOWNORMAL)
    UpdateWindow(hwnd)
    mov hMenu,GetMenu(hwnd)

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    mov rax,msg.wParam
    ret

WinMain endp

WinStart proc
    mov rbx,GetModuleHandle(0)
    ExitProcess(WinMain(rbx, 0, GetCommandLine(), SW_SHOWDEFAULT))
WinStart endp

RCBEGIN

    RCTYPES 1
    RCENTRY RT_MENU
    RCENUMN 1
    RCENUMX IDR_MAINMENU
    RCLANGX LANGID_US

    MENUBEGIN
      MENUNAME "&Thread", MF_END
        MENUITEM IDM_START_THREAD, "&Run Thread"
        MENUITEM IDM_STOP_THREAD,  "&Stop Thread"
        SEPARATOR
        MENUITEM IDM_EXIT, "E&xit", MF_END
    MENUEND

RCEND

    end WinStart
