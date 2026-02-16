; TEST.ASM--
;
; https://blogs.msdn.microsoft.com/oldnewthing/20181023-00/?p=100035
;

define STRICT 1
include windows.inc
include windowsx.inc
include commctrl.inc
include strsafe.inc
include tchar.inc

.data
g_hinst     HINSTANCE 0 ;; This application's HINSTANCE
g_hwndChild HWND 0      ;; Optional child window

.code


;;
;;  OnSize
;;      If we have an inner child, resize it to fit.
;;

OnSize proc hwnd:HWND, state:UINT, x:SINT, y:SINT
    .if (g_hwndChild)
        MoveWindow(g_hwndChild, 0, 0, ldr(x), ldr(y), TRUE)
    .endif
    ret
    endp

SwapKeys proc wParam:WPARAM, vk1:UINT, vk2:UINT

    ldr rcx,wParam
    ldr edx,vk1
    ldr eax,vk2
    .if ( ecx != edx )
        .if ( ecx == eax )
            mov eax,edx
        .else
            mov eax,ecx
        .endif
    .endif
    ret
    endp

TrackbarKeyProc proc WINAPI uses rsi hwnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM,
        uIdSubclass:UINT_PTR, dwRefData:DWORD_PTR

  local delta:SINT
  local pos:SINT
  local style:DWORD

    ldr rsi,wParam
    mov delta,0

    .if (uMsg == WM_KEYDOWN && GetKeyState(VK_CONTROL) & 0x8000)

        .if (GetWindowExStyle(hwnd) & WS_EX_LAYOUTRTL)
            mov esi,SwapKeys(wParam, VK_LEFT, VK_RIGHT)
        .endif

        mov style,GetWindowStyle(hwnd)
        .if (eax & TBS_DOWNISLEFT)
            .if (eax & TBS_VERT)
                mov esi,SwapKeys(wParam, VK_LEFT, VK_RIGHT)
            .else
                mov esi,SwapKeys(wParam, VK_UP, VK_DOWN)
            .endif
        .endif

        .if ( esi == VK_LEFT || esi == VK_UP )
            mov delta,-1
        .elseif ( esi == VK_RIGHT || esi == VK_DOWN )
            mov delta,+1
        .endif


        .if (delta)

            SendMessage(hwnd, TBM_GETPOS, 0, 0)
            add eax,delta
            SendMessage(hwnd, TBM_SETPOS, TRUE, eax)
            GetParent(hwnd)
            .if delta < 0
                FORWARD_WM_HSCROLL(rax, hwnd, TB_LINEUP, 0, SendMessage)
            .else
                FORWARD_WM_HSCROLL(rax, hwnd, TB_LINEDOWN, 0, SendMessage)
            .endif
            SendMessage(hwnd, WM_CHANGEUISTATE, MAKELONG(UIS_CLEAR, UISF_HIDEFOCUS), 0)
            .return 0
        .endif
    .endif
    DefSubclassProc(hwnd, uMsg, wParam, lParam)
    ret
    endp

;;
;;  OnCreate
;;      Applications will typically override this and maybe even
;;      create a child window.
;;

OnCreate proc hwnd:HWND, lpcs:LPCREATESTRUCT

    mov g_hwndChild,CreateWindow(TRACKBAR_CLASS, "", WS_CHILD or WS_VISIBLE, 0, 0, 100, 100, ldr(hwnd), 100, g_hinst, 0)
    SendMessage(g_hwndChild, TBM_SETLINESIZE, 0, 5)
    SendMessage(g_hwndChild, TBM_SETPAGESIZE, 0, 20)
    SetWindowSubclass(g_hwndChild, &TrackbarKeyProc, 0, 0)
    mov eax,TRUE
    ret
    endp

;;
;;  OnDestroy
;;      Post a quit message because our application is over when the
;;      user closes this window.
;;

OnDestroy proc hwnd:HWND
    RemoveWindowSubclass(g_hwndChild, TrackbarKeyProc, 0)
    PostQuitMessage(0)
    ret
    endp

;;
;;  PaintContent
;;      Interesting things will be painted here eventually.
;;

PaintContent proc hwnd:HWND, pps:ptr PAINTSTRUCT
    ret
    endp

;;
;;  OnPaint
;;      Paint the content as part of the paint cycle.
;;

OnPaint proc hwnd:HWND

  local ps:PAINTSTRUCT

    BeginPaint(hwnd, &ps)
    PaintContent(hwnd, &ps)
    EndPaint(hwnd, &ps)
    ret
    endp

;;
;;  OnPrintClient
;;      Paint the content as requested by USER.
;;

OnPrintClient proc hwnd:HWND, hdc:HDC

  local ps:PAINTSTRUCT

    mov ps.hdc,ldr(hdc)
    GetClientRect(ldr(hwnd), &ps.rcPaint)
    PaintContent(hwnd, &ps)
    ret
    endp

OnHScroll proc hwnd:HWND, hwndCtl:HWND, code:UINT, pos:SINT

  local buf[128]:TCHAR

    ldr rcx,hwndCtl
    .if ( rcx == g_hwndChild )
        SendMessage(rcx, TBM_GETPOS, 0, 0)
        StringCchPrintf(&buf, ARRAYSIZE(buf), "pos = %d", eax)
        SetWindowText(hwnd, &buf)
    .endif
    ret
    endp

;;
;;  Window procedure
;;

WndProc proc WINAPI hwnd:HWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch ldr(uiMsg)
    HANDLE_MSG(ldr(hwnd), WM_CREATE, OnCreate)
    HANDLE_MSG(ldr(hwnd), WM_SIZE, OnSize)
    HANDLE_MSG(ldr(hwnd), WM_DESTROY, OnDestroy)
    HANDLE_MSG(ldr(hwnd), WM_PAINT, OnPaint)
    HANDLE_MSG(ldr(hwnd), WM_HSCROLL, OnHScroll)
    .case WM_PRINTCLIENT
        OnPrintClient(ldr(hwnd), ldr(wParam))
        .return 0
    .endsw
    DefWindowProc(ldr(hwnd), ldr(uiMsg), ldr(wParam), ldr(lParam))
    ret
    endp


InitApp proc

  local wc:WNDCLASSEX

    mov wc.cbSize,          WNDCLASSEX
    mov wc.hInstance,       g_hinst
    mov wc.lpfnWndProc,     &WndProc
    xor eax,eax
    mov wc.style,           eax
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hIcon,           rax
    mov wc.hIconSm,         rax
    mov wc.lpszMenuName,    rax
    mov wc.hCursor,         LoadCursor(NULL, IDC_ARROW)
    mov wc.hbrBackground,   (COLOR_WINDOW + 1)
    mov wc.lpszClassName,   &@CStr("Scratch")
    .if RegisterClassEx(&wc)
        InitCommonControls()    ;; In case we use a common control
        mov eax,TRUE
    .endif
    ret
    endp


_tWinMain proc WINAPI hinst:HINSTANCE, hinstPrev:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local msg:MSG
  local hwnd:HWND

    mov g_hinst,ldr(hinst)

    .return .if !InitApp()
    .return .ifsd !SUCCEEDED(CoInitialize(NULL)) ;; In case we use COM

    mov hwnd,CreateWindowEx(
            0,
            "Scratch",                      ;; Class Name
            "Scratch",                      ;; Title
            WS_OVERLAPPEDWINDOW,            ;; Style
            CW_USEDEFAULT, CW_USEDEFAULT,   ;; Position
            CW_USEDEFAULT, CW_USEDEFAULT,   ;; Size
            NULL,                           ;; Parent
            NULL,                           ;; No menu
            hinst,                          ;; Instance
            0)                              ;; No special parameters

    ShowWindow(hwnd, nShowCmd)
    .while GetMessage(&msg, NULL, 0, 0)
        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw
    CoUninitialize()
    xor eax,eax
    ret
    endp

    end _tstart
