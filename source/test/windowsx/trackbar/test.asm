; TEST.ASM--
;
; https://blogs.msdn.microsoft.com/oldnewthing/20181023-00/?p=100035
;

STRICT equ 1
include windows.inc
include windowsx.inc
include commctrl.inc
include strsafe.inc

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
        MoveWindow(g_hwndChild, 0, 0, x, y, TRUE)
    .endif
    ret

OnSize endp

SwapKeys proc wParam:WPARAM, vk1:UINT, vk2:UINT

    mov ecx,wParam
    mov edx,vk1
    mov eax,vk2
    .return .if (ecx == edx)
    .return edx .if (ecx == eax)
    mov eax,ecx
    ret

SwapKeys endp

TrackbarKeyProc proc WINAPI hwnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM,
        uIdSubclass:UINT_PTR, dwRefData:DWORD_PTR

  local delta:SINT
  local pos:SINT
  local style:DWORD

    mov delta,0

    .if (uMsg == WM_KEYDOWN && GetKeyState(VK_CONTROL) & 0x8000)

        .if (GetWindowExStyle(hwnd) & WS_EX_LAYOUTRTL)
            mov wParam,SwapKeys(wParam, VK_LEFT, VK_RIGHT)
        .endif

        mov style,GetWindowStyle(hwnd)
        .if (eax & TBS_DOWNISLEFT)
            .if (eax & TBS_VERT)
                mov wParam,SwapKeys(wParam, VK_LEFT, VK_RIGHT)
            .else
                mov wParam,SwapKeys(wParam, VK_UP, VK_DOWN)
            .endif
        .endif

        .if (wParam == VK_LEFT || wParam == VK_UP)
            mov delta,-1
        .elseif (wParam == VK_RIGHT || wParam == VK_DOWN)
            mov delta,+1
        .endif


        .if (delta)

            SendMessage(hwnd, TBM_GETPOS, 0, 0)
            add eax,delta
            SendMessage(hwnd, TBM_SETPOS, TRUE, eax)
            GetParent(hwnd)
            .if delta < 0
                FORWARD_WM_HSCROLL(eax, hwnd, TB_LINEUP, 0, SendMessage)
            .else
                FORWARD_WM_HSCROLL(eax, hwnd, TB_LINEDOWN, 0, SendMessage)
            .endif
            SendMessage(hwnd, WM_CHANGEUISTATE, MAKELONG(UIS_CLEAR, UISF_HIDEFOCUS), 0)
            .return 0
        .endif
    .endif
    DefSubclassProc(hwnd, uMsg, wParam, lParam)
    ret

TrackbarKeyProc endp

;;
;;  OnCreate
;;      Applications will typically override this and maybe even
;;      create a child window.
;;

OnCreate proc hwnd:HWND, lpcs:LPCREATESTRUCT

    CreateWindow(TRACKBAR_CLASS, "", WS_CHILD or WS_VISIBLE, 0, 0, 100, 100, hwnd, 100, g_hinst, 0)
    mov g_hwndChild,eax

    SendMessage(g_hwndChild, TBM_SETLINESIZE, 0, 5)
    SendMessage(g_hwndChild, TBM_SETPAGESIZE, 0, 20)

    SetWindowSubclass(g_hwndChild, TrackbarKeyProc, 0, 0)
    mov eax,TRUE
    ret

OnCreate endp

;;
;;  OnDestroy
;;      Post a quit message because our application is over when the
;;      user closes this window.
;;

OnDestroy proc hwnd:HWND

    RemoveWindowSubclass(g_hwndChild, TrackbarKeyProc, 0)
    PostQuitMessage(0)
    ret

OnDestroy endp

;;
;;  PaintContent
;;      Interesting things will be painted here eventually.
;;

PaintContent proc hwnd:HWND, pps:ptr PAINTSTRUCT
    ret
PaintContent endp

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

OnPaint endp

;;
;;  OnPrintClient
;;      Paint the content as requested by USER.
;;

OnPrintClient proc hwnd:HWND, hdc:HDC

  local ps:PAINTSTRUCT

    mov eax,hdc
    mov ps.hdc,eax
    GetClientRect(hwnd, &ps.rcPaint)
    PaintContent(hwnd, &ps)
    ret

OnPrintClient endp

OnHScroll proc hwnd:HWND, hwndCtl:HWND, code:UINT, pos:SINT

  local buf[128]:TCHAR

    mov eax,hwndCtl
    .if (eax == g_hwndChild)

        SendMessage(hwndCtl, TBM_GETPOS, 0, 0)

        StringCchPrintf(&buf, ARRAYSIZE(buf), "pos = %d", eax)
        SetWindowText(hwnd, &buf)
    .endif
    ret

OnHScroll endp

;;
;;  Window procedure
;;

WndProc proc WINAPI hwnd:HWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (uiMsg)

    HANDLE_MSG(hwnd, WM_CREATE, OnCreate)
    HANDLE_MSG(hwnd, WM_SIZE, OnSize)
    HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy)
    HANDLE_MSG(hwnd, WM_PAINT, OnPaint)
    HANDLE_MSG(hwnd, WM_HSCROLL, OnHScroll)

    .case WM_PRINTCLIENT
        OnPrintClient(hwnd, wParam)
        .return 0
    .endsw
    DefWindowProc(hwnd, uiMsg, wParam, lParam)
    ret

WndProc endp

InitApp proc

  local wc:WNDCLASSEX

    mov wc.cbSize,          WNDCLASSEX
    mov wc.hInstance,       g_hinst
    mov wc.lpfnWndProc,     &WndProc
    xor eax,eax
    mov wc.style,           eax
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hIcon,           eax
    mov wc.hIconSm,         eax
    mov wc.lpszMenuName,    eax
    mov wc.hCursor,         LoadCursor(NULL, IDC_ARROW)
    mov wc.hbrBackground,   (COLOR_WINDOW + 1)
    mov wc.lpszClassName,   &@CStr("Scratch")

    .if RegisterClassEx(&wc)

        InitCommonControls()    ;; In case we use a common control
        mov eax,TRUE
    .endif
    ret

InitApp endp

WinMain proc WINAPI hinst:HINSTANCE, hinstPrev:HINSTANCE, lpCmdLine:LPSTR, nShowCmd:SINT

  local msg:MSG
  local hwnd:HWND

    mov eax,hinst
    mov g_hinst,eax

    .return .if !InitApp()
    .return .ifsd !SUCCEEDED(CoInitialize(NULL)) ;; In case we use COM

    CreateWindowEx(
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

    mov hwnd,eax
    ShowWindow(hwnd, nShowCmd)

    .while GetMessage(&msg, NULL, 0, 0)

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw

    CoUninitialize()
    xor eax,eax
    ret

WinMain endp

    end
