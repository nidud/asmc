; TEST.ASM--
;
; https://blogs.msdn.microsoft.com/oldnewthing/20030723-00/?p=43073
;

STRICT equ 1
include windows.inc
include windowsx.inc
include ole2.inc
include commctrl.inc
include shlwapi.inc

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

;;
;;  OnCreate
;;      Applications will typically override this and maybe even
;;      create a child window.
;;

OnCreate proc hwnd:HWND, lpcs:LPCREATESTRUCT

    mov eax,TRUE
    ret

OnCreate endp

;;
;;  OnDestroy
;;      Post a quit message because our application is over when the
;;      user closes this window.
;;

OnDestroy proc hwnd:HWND

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

    mov ps.hdc,rdx; hdc;
    GetClientRect(hwnd, &ps.rcPaint)
    PaintContent(hwnd, &ps)
    ret

OnPrintClient endp

;;
;;  Window procedure
;;

WndProc proc hwnd:HWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (uiMsg)

        HANDLE_MSG(hwnd, WM_CREATE, OnCreate)
        HANDLE_MSG(hwnd, WM_SIZE, OnSize)
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy)
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint)

        .case WM_PRINTCLIENT
            OnPrintClient(hwnd, wParam)
            .return 0
    .endsw
    DefWindowProc(hwnd, uiMsg, wParam, lParam)
    ret

WndProc endp

InitApp proc

  local wc:WNDCLASSEX

    xor eax,eax
    mov wc.cbSize,          WNDCLASSEX
    mov wc.style,           eax
    mov wc.cbClsExtra,      eax
    mov wc.cbWndExtra,      eax
    mov wc.hIcon,           rax
    mov wc.lpszMenuName,    rax
    mov wc.lpfnWndProc,     &WndProc
    mov wc.hInstance,       g_hinst
    mov wc.hCursor,         LoadCursor(NULL, IDC_ARROW)
    mov wc.hbrBackground,   (COLOR_WINDOW + 1)
    mov wc.lpszClassName,   &@CStr("Scratch")

    .if RegisterClassEx(&wc)

        InitCommonControls()    ;; In case we use a common control
        mov eax,TRUE
    .endif
    ret

InitApp endp

WinMain proc hinst:HINSTANCE, hinstPrev:HINSTANCE,
                   lpCmdLine:LPSTR, nShowCmd:SINT

  local msg:MSG
  local hwnd:HWND

    mov g_hinst,rcx ; hinst

    .return .if !InitApp()
    CoInitialize(NULL)
    .return .ifsd !SUCCEEDED(eax) ;; In case we use COM

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

    mov hwnd,rax
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
