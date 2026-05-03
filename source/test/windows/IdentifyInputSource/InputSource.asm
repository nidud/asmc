
include stdafx.inc

;; Global Variables

.data

g_hwnd HWND NULL
g_inputSource INPUT_MESSAGE_SOURCE <>

.code

;;
;; InputSourceApp::Initialize
;;
;; This method is used to create and display the application
;; window, and provides a convenient place to create any device
;; independent resources that will be required.
;;

Initialize proc private hInstance:HINSTANCE

    local wcex:WNDCLASSEX
    local atom:ATOM

    ;; Register window class

    mov wcex.cbSize,        WNDCLASSEX
    mov wcex.style,         CS_HREDRAW or CS_VREDRAW
    mov wcex.lpfnWndProc,   &WndProc
    mov wcex.cbClsExtra,    0
    mov wcex.cbWndExtra,    LONG_PTR
    mov wcex.hInstance,     hInstance
    mov wcex.hIcon,         LoadIcon(NULL, IDI_APPLICATION)
    mov wcex.hCursor,       LoadCursor(NULL, IDC_ARROW)
    mov wcex.hbrBackground, NULL
    mov wcex.lpszMenuName,  NULL
    mov wcex.lpszClassName, &@CStr("InputSourceApp")
    mov wcex.hIconSm,       LoadIcon(NULL, IDI_APPLICATION)
    mov atom,RegisterClassEx(&wcex)

    SetProcessDPIAware()

    ;; Create window
    mov g_hwnd,CreateWindowEx(0,
        "InputSourceApp",
        "Input Source Identification Sample",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, hInstance, NULL)

    .if (g_hwnd)

        ShowWindow(
            g_hwnd,
            SW_SHOWNORMAL
            )

        UpdateWindow(
            g_hwnd
            )
    .endif

    .return S_OK .if g_hwnd
    .return E_FAIL

Initialize endp


OnRender proc private hdc:HDC, rcPaint:ptr RECT

    .new wzText[512]:WCHAR = 0

    FillRect(hdc, rcPaint, GetStockObject(WHITE_BRUSH))
    wcscpy(&wzText, "Source: ")

    .switch(g_inputSource.deviceType)
    .case IMDT_UNAVAILABLE
        wcscat(&wzText, "Unavailable\n")
        .endc
    .case IMDT_KEYBOARD
        wcscat(&wzText, "Keyboard\n")
        .endc
    .case IMDT_MOUSE
        wcscat(&wzText, "Mouse\n")
        .endc
    .case IMDT_TOUCH
        wcscat(&wzText, "Touch\n")
        .endc
    .case IMDT_PEN
        wcscat(&wzText, "Pen\n")
        .endc
    .endsw

    wcscat(&wzText, "Origin: ")
    .switch(g_inputSource.originId)
    .case IMO_UNAVAILABLE
        wcscat(&wzText, "Unavailable\n")
        .endc
    .case IMO_HARDWARE
        wcscat(&wzText, "Hardware\n")
        .endc
    .case IMO_INJECTED
        wcscat(&wzText, "Injected\n")
        .endc
    .case IMO_SYSTEM
        wcscat(&wzText, "System\n")
        .endc
    .endsw

    DrawText(hdc, &wzText, wcslen(&wzText), rcPaint, DT_TOP or DT_LEFT)
    .return S_OK

OnRender endp


;;
;; WndProc
;;
;; This static method handles our app's window messages
;;

WndProc proc private hwnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .if ((message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) || \
         (message >= WM_KEYFIRST && message <= WM_KEYLAST) || \
         (message >= WM_TOUCH && message <= WM_POINTERWHEEL))

        GetCurrentInputMessageSource(&g_inputSource)
        InvalidateRect(g_hwnd, NULL, FALSE)
    .endif

    .switch (message)
    .case WM_PAINT
    .case WM_DISPLAYCHANGE
        .new ps:PAINTSTRUCT
         OnRender(BeginPaint(hwnd, &ps), &ps.rcPaint)
         EndPaint(hwnd, &ps)
        .return 0
    .case WM_DESTROY
         PostQuitMessage(0)
        .return 1
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if wParam == VK_ESCAPE
    .endsw
    .return DefWindowProc(hwnd, message, wParam, lParam)

WndProc endp

;;
;; WinMain
;;
;; Application entrypoint
;;

wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE,
        lpCmdLine:LPWSTR, nCmdShow:int_t

    .new hr:HRESULT = E_FAIL

    ZeroMemory(&g_inputSource, sizeof(g_inputSource))
    mov hr,Initialize(hInstance)
    .if (SUCCEEDED(hr))

        .new msg:MSG

        .while GetMessage(&msg, NULL, 0, 0)

            TranslateMessage(&msg)
            DispatchMessage(&msg)
        .endw
    .endif

    .return 0 .if SUCCEEDED(hr)
    .return 1

wWinMain endp

    end _tstart
