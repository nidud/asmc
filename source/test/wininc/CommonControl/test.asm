;
; http://win32assembly.programminghorizon.com/tut18.html
;
include windows.inc
include commctrl.inc
include tchar.inc

ifdef _WIN64
APPNAME         equ <"Common Control Demo 64">
else
APPNAME         equ <"Common Control Demo 32">
endif
CLASSNAME       equ <"CommonControlWinClass">

IDC_PROGRESS    equ 1 ; control IDs
IDC_STATUS      equ 2
IDC_TIMER       equ 3

.data
hInstance       HINSTANCE ?
hwndProgress    HANDLE ?
hwndStatus      HANDLE ?
CurrentStep     dd ?
TimerID         dd 0

.code

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch uMsg

      .case WM_DESTROY
        PostQuitMessage(NULL)
        .if TimerID
            KillTimer(hWnd, TimerID)
        .endif
        xor eax,eax
        .endc

      .case WM_CREATE
        mov hwndProgress,CreateWindowEx(NULL, "msctls_progress32", NULL, WS_CHILD or WS_VISIBLE,
            100, 200, 300, 20, hWnd, IDC_PROGRESS, hInstance, NULL)

        mov eax,1000  ; the lParam of PBM_SETRANGE message contains the range
        mov CurrentStep,eax
        shl eax,16    ; the high range is in the high word

        SendMessage(hwndProgress, PBM_SETRANGE, 0, eax)
        SendMessage(hwndProgress, PBM_SETSTEP, 10, 0)
        mov hwndStatus,CreateStatusWindow(WS_CHILD or WS_VISIBLE, NULL, hWnd, IDC_STATUS)
        SetTimer(hWnd, IDC_TIMER, 100, NULL) ; create a timer
        mov TimerID,eax
        xor eax,eax
        .endc

      .case WM_TIMER
        SendMessage(hwndProgress, PBM_STEPIT, 0, 0)
        sub CurrentStep,10
        .if !CurrentStep
            KillTimer(hWnd, TimerID)
            mov TimerID,0
            SendMessage(hwndStatus, SB_SETTEXT, 0, "Finished!")
            MessageBox(hWnd, "Finished!", APPNAME, MB_OK or MB_ICONINFORMATION)
            SendMessage(hwndStatus, SB_SETTEXT, 0, 0)
            SendMessage(hwndProgress, PBM_SETPOS, 0, 0)
        .endif
        xor eax,eax
        .endc

      .default
        DefWindowProc(hWnd, uMsg, wParam, lParam)
    .endsw
    ret

WndProc endp

_tWinMain proc WINAPI hInst: HINSTANCE,
     hPrevInstance: HINSTANCE,
         lpCmdLine: LPTSTR,
          nShowCmd: SINT

    local wc:WNDCLASSEX
    local msg:MSG
    local hwnd:HWND

    mov wc.cbSize,sizeof(WNDCLASSEX)
    mov wc.style,CS_HREDRAW or CS_VREDRAW
    lea rax,WndProc
    mov wc.lpfnWndProc,rax
    push hInst
    pop wc.hInstance
    mov wc.cbClsExtra,0
    mov wc.cbWndExtra,0
    mov wc.hbrBackground,COLOR_APPWORKSPACE
    mov wc.lpszMenuName,NULL
    lea rax,@CStr("CommonControlWinClass")
    mov wc.lpszClassName,rax
    mov wc.hIcon,LoadIcon(0, IDI_APPLICATION)
    mov wc.hIconSm,rax
    mov wc.hCursor,LoadCursor(0, IDC_ARROW)
    RegisterClassEx(&wc)
    mov hwnd,CreateWindowEx(WS_EX_CLIENTEDGE, CLASSNAME, APPNAME,
        WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX or WS_MAXIMIZEBOX or WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL)

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    mov rax,msg.wParam
    ret

_tWinMain endp

    end _tstart
