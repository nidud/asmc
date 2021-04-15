;;
;; https://github.com/microsoft/Windows-classic-samples
;;
;; File: MagnifierSample.asm
;;
;; Description: Implements a simple control that magnifies the screen, using the
;; Magnification API.
;;
;; The magnification window is quarter-screen by default but can be resized.
;; To make it full-screen, use the Maximize button or double-click the caption
;; bar. To return to partial-screen mode, click on the application icon in the
;; taskbar and press ESC.
;;
;; In full-screen mode, all keystrokes and mouse clicks are passed through to the
;; underlying focused application. In partial-screen mode, the window can receive
;; the focus.
;;
;; Multiple monitors are not supported.
;;
;;
;; Requirements: To compile, link to Magnification.lib. The sample must be run
;; with elevated privileges.
;;
;; The sample is not designed for multimonitor setups.
;;

;; Ensure that the following definition is in effect before winuser.h is included.

ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0601
endif

include windows.inc
include wincodec.inc
include magnification.inc
include tchar.inc

option dllimport:none

;; For simplicity, the sample uses a constant magnification factor.

define MAGFACTOR  2.0
define RESTOREDWINDOWSTYLES WS_SIZEBOX or WS_SYSMENU or WS_CLIPCHILDREN or WS_CAPTION or WS_MAXIMIZEBOX

;; Forward declarations.

RegisterHostWindowClass proto hInstance:HINSTANCE
SetupMagnifier      proto hinst:HINSTANCE
WndProc             proto :HWND, :UINT, :WPARAM, :LPARAM
UpdateMagWindow     proto hwnd:HWND, uMsg:UINT, idEvent:UINT_PTR, dwTime:DWORD
GoFullScreen        proto
GoPartialScreen     proto

;; Global variables and strings.
.data

hInst               HINSTANCE 0
WindowClassName     equ <"MagnifierWindow">
WindowTitle         equ <"Screen Magnifier Sample">
timerInterval       equ 16 ;; close to the refresh rate @60hz
hwndMag             HWND 0
hwndHost            HWND 0
magWindowRect       RECT <>
hostWindowRect      RECT <>
isFullScreen        BOOL FALSE

.code

;;
;; FUNCTION: WinMain()
;;
;; PURPOSE: Entry point for the application.
;;

WinMain proc WINAPI hInstance:HINSTANCE,
                    hPrevInstance:HINSTANCE,
                    lpCmdLine:LPSTR,
                    nCmdShow:int_t

    .if (MagInitialize() == FALSE)

        .return 0
    .endif
    .if (SetupMagnifier(hInstance) == FALSE)

        .return 0
    .endif

    ShowWindow(hwndHost, nCmdShow)
    UpdateWindow(hwndHost)

    ;; Create a timer to update the control.

    .new timerId:UINT = SetTimer(hwndHost, 0, timerInterval, &UpdateMagWindow)

    ;; Main message loop.

    .new msg:MSG
    .while (GetMessage(&msg, NULL, 0, 0))

        TranslateMessage(&msg)
        DispatchMessage(&msg)
    .endw

    ;; Shut down.

    KillTimer(NULL, timerId)
    MagUninitialize()

    .return msg.wParam

WinMain endp

;;
;; FUNCTION: HostWndProc()
;;
;; PURPOSE: Window procedure for the window that hosts the magnifier control.
;;

HostWndProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

    .case WM_KEYDOWN
        .if (wParam == VK_ESCAPE)

            .if (isFullScreen)

                GoPartialScreen()
            .endif
        .endif
        .endc

    .case WM_SYSCOMMAND
        .if (GET_SC_WPARAM(wParam) == SC_MAXIMIZE)

            GoFullScreen()

        .else

            .return DefWindowProc(hWnd, message, wParam, lParam)
        .endif
        .endc

    .case WM_DESTROY
        PostQuitMessage(0)
        .endc
    .case WM_CHAR
        .gotosw(WM_DESTROY) .if GET_SC_WPARAM(wParam) == VK_ESCAPE

    .case WM_SIZE
        .if ( hwndMag != NULL )

            GetClientRect(hWnd, &magWindowRect)
            ;; Resize the control to fill the window.
            SetWindowPos(hwndMag, NULL,
                magWindowRect.left, magWindowRect.top, magWindowRect.right, magWindowRect.bottom, 0)
        .endif
        .endc

    .default
        .return DefWindowProc(hWnd, message, wParam, lParam)
    .endsw
    .return 0

HostWndProc endp

;;
;;  FUNCTION: RegisterHostWindowClass()
;;
;;  PURPOSE: Registers the window class for the window that contains the magnification control.
;;

RegisterHostWindowClass proc hInstance:HINSTANCE

    .new wcex:WNDCLASSEX = {
            sizeof(wcex),
            CS_HREDRAW or CS_VREDRAW,
            &HostWndProc,
            0,
            hInstance,
            NULL,
            NULL,
            LoadCursor(NULL, IDC_ARROW),
            (1 + COLOR_BTNFACE),
            0,
            &@CStr(WindowClassName),
            NULL }
    .return RegisterClassEx(&wcex)
RegisterHostWindowClass endp

;;
;; FUNCTION: SetupMagnifier
;;
;; PURPOSE: Creates the windows and initializes magnification.
;;

SetupMagnifier proc hinst:HINSTANCE

    ;; Set bounds of host window according to screen size.

    mov hostWindowRect.top,0
    GetSystemMetrics(SM_CYSCREEN)
    shr eax,2
    mov hostWindowRect.bottom,eax ;; top quarter of screen
    mov hostWindowRect.left,0
    mov hostWindowRect.right,GetSystemMetrics(SM_CXSCREEN)

    ;; Create the host window.

    RegisterHostWindowClass(hinst);
    mov hwndHost,CreateWindowEx(WS_EX_TOPMOST or WS_EX_LAYERED,
        WindowClassName, WindowTitle,
        RESTOREDWINDOWSTYLES,
        0, 0, hostWindowRect.right, hostWindowRect.bottom, NULL, NULL, hInst, NULL)

    .return FALSE .if (!hwndHost)

    ;; Make the window opaque.

    SetLayeredWindowAttributes(hwndHost, 0, 255, LWA_ALPHA)

    ;; Create a magnifier control that fills the client area.

    GetClientRect(hwndHost, &magWindowRect)
    mov hwndMag,CreateWindow(WC_MAGNIFIER, "MagnifierWindow",
        WS_CHILD or MS_SHOWMAGNIFIEDCURSOR or WS_VISIBLE,
        magWindowRect.left, magWindowRect.top, magWindowRect.right, magWindowRect.bottom, hwndHost, NULL, hInst, NULL )

    .return FALSE .if (!hwndMag)

    ;; Set the magnification factor.

   .new matrix:MAGTRANSFORM = {{
          MAGFACTOR, 0.0, 0.0,
          0.0, MAGFACTOR, 0.0,
          0.0, 0.0, 1.0
        }}

    .new retval:BOOL = MagSetWindowTransform(hwndMag, &matrix)

    .if (retval)

        .new magEffectInvert:MAGCOLOREFFECT = {{
            -1.0,  0.0,  0.0,  0.0,  0.0,
             0.0, -1.0,  0.0,  0.0,  0.0,
             0.0,  0.0, -1.0,  0.0,  0.0,
             0.0,  0.0,  0.0,  1.0,  0.0,
             1.0,  1.0,  1.0,  0.0,  1.0
            }}

        mov retval,MagSetColorEffect(hwndMag, &magEffectInvert)
    .endif

    .return retval

SetupMagnifier endp


;;
;; FUNCTION: UpdateMagWindow()
;;
;; PURPOSE: Sets the source rectangle and updates the window. Called by a timer.
;;

UpdateMagWindow proc hwnd:HWND, uMsg:UINT, idEvent:UINT_PTR, dwTime:DWORD

   .new mousePoint:POINT

    GetCursorPos(&mousePoint)

   .new width:int_t
    mov eax,magWindowRect.right
    sub eax,magWindowRect.left
    shr eax,1
    mov width,eax

   .new height:int_t
    mov eax,magWindowRect.bottom
    sub eax,magWindowRect.top
    shr eax,1
    mov height,eax

   .new sourceRect:RECT
    mov eax,mousePoint.x
    mov ecx,width
    shr ecx,1
    sub eax,ecx
    mov sourceRect.left,eax
    mov eax,mousePoint.y
    mov ecx,height
    shr ecx,1
    sub eax,ecx
    mov sourceRect.top,eax

    ;; Don't scroll outside desktop area.
    .if (sourceRect.left < 0)

        mov sourceRect.left,0
    .endif
    GetSystemMetrics(SM_CXSCREEN)
    sub eax,width
    .if (sourceRect.left > eax )

        mov sourceRect.left,eax
    .endif
    mov eax,sourceRect.left
    add eax,width
    mov sourceRect.right,eax

    .ifs (sourceRect.top < 0)

        mov sourceRect.top,0
    .endif

    GetSystemMetrics(SM_CYSCREEN)
    sub eax,height
    .if ( sourceRect.top >  eax )
        mov sourceRect.top,eax
    .endif
    mov eax,sourceRect.top
    add eax,height
    mov sourceRect.bottom,eax

    ;; Set the source rectangle for the magnifier control.
    MagSetWindowSource(hwndMag, sourceRect)

    ;; Reclaim topmost status, to prevent unmagnified menus from remaining in view.
    SetWindowPos(hwndHost, HWND_TOPMOST, 0, 0, 0, 0,
        SWP_NOACTIVATE or SWP_NOMOVE or SWP_NOSIZE )

    ;; Force redraw.
    InvalidateRect(hwndMag, NULL, TRUE)
    ret

UpdateMagWindow endp

;;
;; FUNCTION: GoFullScreen()
;;
;; PURPOSE: Makes the host window full-screen by placing non-client elements outside the display.
;;

GoFullScreen proc

    mov isFullScreen,TRUE
    ;; The window must be styled as layered for proper rendering.
    ;; It is styled as transparent so that it does not capture mouse clicks.
    SetWindowLong(hwndHost, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED or WS_EX_TRANSPARENT)
    ;; Give the window a system menu so it can be closed on the taskbar.
    SetWindowLong(hwndHost, GWL_STYLE, WS_CAPTION or WS_SYSMENU)

    ;; Calculate the span of the display area.

    .new hDC:HDC = GetDC(NULL)
    .new xSpan:int_t = GetSystemMetrics(SM_CXSCREEN)
    .new ySpan:int_t = GetSystemMetrics(SM_CYSCREEN)

    ReleaseDC(NULL, hDC)

    ;; Calculate the size of system elements.

    .new xBorder:int_t  = GetSystemMetrics(SM_CXFRAME)
    .new yCaption:int_t = GetSystemMetrics(SM_CYCAPTION)
    .new yBorder:int_t  = GetSystemMetrics(SM_CYFRAME)

    ;; Calculate the window origin and span for full-screen mode.

    mov eax,xBorder
    neg eax
    .new xOrigin:int_t = eax
    mov eax,yBorder
    neg eax
    sub eax,yCaption

    .new yOrigin:int_t = eax

    mov eax,xBorder
    add eax,eax
    mov xSpan,eax
    mov eax,yBorder
    add eax,eax
    add eax,yCaption
    mov ySpan,eax

    SetWindowPos(hwndHost, HWND_TOPMOST, xOrigin, yOrigin, xSpan, ySpan,
        SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

GoFullScreen endp

;;
;; FUNCTION: GoPartialScreen()
;;
;; PURPOSE: Makes the host window resizable and focusable.
;;

GoPartialScreen proc

    mov isFullScreen,FALSE

    SetWindowLong(hwndHost, GWL_EXSTYLE, WS_EX_TOPMOST or WS_EX_LAYERED)
    SetWindowLong(hwndHost, GWL_STYLE, RESTOREDWINDOWSTYLES)
    SetWindowPos(hwndHost, HWND_TOPMOST,
        hostWindowRect.left, hostWindowRect.top, hostWindowRect.right, hostWindowRect.bottom,
        SWP_SHOWWINDOW or SWP_NOZORDER or SWP_NOACTIVATE)
    ret

GoPartialScreen endp

    end _tstart
