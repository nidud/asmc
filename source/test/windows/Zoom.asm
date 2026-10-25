; ZOOM.ASM--
;
; A Windows Magnifier with a point of interest:
; - same as Ctrl+Alt+MouseWheel but using Shift and Mouse x,y as base
; - same as Ctrl+Alt+arrow keys but using Shift+Mouse-Left
;
include windows.inc
include magnification.inc
include winres.inc
include stdio.inc
include tchar.inc

option dllimport:none

define IDD_WINZOOM      101
define IDC_CLOSE        1001

define MAGZOOM_MIN      1.0
define MAGZOOM_MAX      4096.0
define MAGZOOM_STEP     0.1

.data
 g_hwndDlg              HWND NULL
 g_hMouseHook           HHOOK NULL
 g_bDragging            BOOL FALSE
 g_ptDragStart          POINT <0,0>
 g_xOffsetStart         int_t 0
 g_yOffsetStart         int_t 0

.code

ErrorMessage proc hr:HRESULT, format:LPTSTR
    local message[512]:TCHAR, buffer[16]:TCHAR, szMessage:LPTSTR
    ldr edx,hr
    .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)
        mov hr,HRESULT_CODE(edx)
    .endif
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER or FORMAT_MESSAGE_FROM_SYSTEM or FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), &szMessage, 0, NULL)
    _stprintf(&message, "%s\n\nError code: %#X\n\n%s", format, hr, szMessage)
    MessageBox(NULL, &message, "Error", MB_OK or MB_ICONERROR)
    LocalFree(szMessage)
   .return hr
    endp


HandleShiftMouseWheel proc uses rbx lParam:ptr MSLLHOOKSTRUCT
   .new xOffset:int_t
   .new yOffset:int_t
   .new magnificationFactor:real4

    ldr rbx,lParam
    .ifd !MagGetFullscreenTransform(&magnificationFactor, &xOffset, &yOffset)
        .return FALSE
    .endif
    movss xmm5,magnificationFactor
    .ifs ( GET_WHEEL_DELTA_WPARAM([rbx].MSLLHOOKSTRUCT.mouseData) > 0 )
        addss xmm5,MAGZOOM_STEP
    .else
        subss xmm5,MAGZOOM_STEP
    .endif
    minss xmm5,MAGZOOM_MAX
    maxss xmm5,MAGZOOM_MIN
    cvtsi2ss xmm0,[rbx].MSLLHOOKSTRUCT.pt.x
    movss xmm1,xmm0
    divss xmm1,xmm5
    subss xmm0,xmm1
    cvtss2si eax,xmm0
    mov xOffset,eax
    cvtsi2ss xmm0,[rbx].MSLLHOOKSTRUCT.pt.y
    movss xmm1,xmm0
    divss xmm1,xmm5
    subss xmm0,xmm1
    cvtss2si eax,xmm0
    mov yOffset,eax
    MagSetFullscreenTransform(xmm5, xOffset, yOffset)
    ret
    endp

HandleShiftMouseDrag proc uses rbx lParam:ptr MSLLHOOKSTRUCT
   .new xOffset:int_t
   .new yOffset:int_t
   .new magnificationFactor:real4

    ldr rbx,lParam
    .ifd !MagGetFullscreenTransform(&magnificationFactor, &xOffset, &yOffset)
        .return
    .endif
    mov eax,g_ptDragStart.x
    sub eax,[rbx].MSLLHOOKSTRUCT.pt.x
    add eax,g_xOffsetStart
    mov xOffset,eax
    mov eax,g_ptDragStart.y
    sub eax,[rbx].MSLLHOOKSTRUCT.pt.y
    add eax,g_yOffsetStart
    mov yOffset,eax
    MagSetFullscreenTransform(magnificationFactor, xOffset, yOffset)
    ret
    endp

LowLevelMouseProc proc uses rbx nCode:int_t, wParam:WPARAM, lParam:LPARAM
    ldr ecx,nCode
    ldr rdx,wParam
    .ifs ( ecx >= 0 )
        ldr rbx,lParam
        .if (edx == WM_MOUSEWHEEL)
            .ifd ( GetAsyncKeyState(VK_SHIFT) & 0x8000 )
                .ifd HandleShiftMouseWheel(rbx)
                    .return
                .endif
            .endif
        .elseif (edx == WM_LBUTTONDOWN)
            .ifd ( GetAsyncKeyState(VK_SHIFT) & 0x8000 )
                mov g_bDragging,TRUE
                mov eax,[rbx].MSLLHOOKSTRUCT.pt.x
                mov g_ptDragStart.x,eax
                mov eax,[rbx].MSLLHOOKSTRUCT.pt.y
                mov g_ptDragStart.y,eax
                .new xOffset:int_t
                .new yOffset:int_t
                .new magnificationFactor:real4
                MagGetFullscreenTransform(&magnificationFactor, &xOffset, &yOffset)
                mov g_xOffsetStart,xOffset
                mov g_yOffsetStart,yOffset
               .return TRUE
            .endif
        .elseif (edx == WM_MOUSEMOVE)
            .ifd (g_bDragging)
                HandleShiftMouseDrag(rbx)
            .endif
        .elseif (edx == WM_LBUTTONUP)
            .ifd (g_bDragging)
                mov g_bDragging,FALSE
               .return TRUE
            .endif
        .endif
    .endif
    .return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam)
    endp

WinZoomProc proc hwndDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .switch ldr(uMsg)
    .case WM_INITDIALOG
        mov g_hwndDlg,hwndDlg
        mov g_hMouseHook,SetWindowsHookEx(WH_MOUSE_LL, &LowLevelMouseProc, GetModuleHandle(NULL), 0)
        .if (!g_hMouseHook)
            ErrorMessage(GetLastError(), "Failed to install mouse hook")
        .endif
       .return FALSE
    .case WM_CLOSE
    .case WM_COMMAND
        EndDialog(hwndDlg, 0)
       .return TRUE
    .case WM_DESTROY
        .if (g_hMouseHook)
            UnhookWindowsHookEx(g_hMouseHook)
            mov g_hMouseHook,NULL
        .endif
        mov g_hwndDlg,NULL
        mov g_bDragging,FALSE
        .return TRUE
    .endsw
    .return FALSE
    endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nCmdShow:int_t
    .if MagInitialize()
        DialogBox(hInstance, MAKEINTRESOURCE(IDD_WINZOOM), NULL, &WinZoomProc)
        MagUninitialize()
    .else
        MessageBox(NULL, L"Failed to initialize magnification.", "Windows Zoom", MB_OK)
    .endif
    .return 0
    endp

    RCBEGIN
    RCTYPES 1
    RCENTRY RT_DIALOG
    RCENUMN 1
    RCENUMX IDD_WINZOOM
    RCLANGX LANGID_US
    STYLE equ DS_SETFONT or DS_MODALFRAME or DS_FIXEDSYS or WS_POPUP or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX
    DIALOGEX STYLE, 4, 100, 100, 160, 130
     CAPTION "Windows Zoom"
     FONT 8, "MS Shell Dlg", 400, 0, 1
      LTEXT "Windows Zoom Version 1.0 Beta",IDC_STATIC,10,10,140,12
      LTEXT "Windows Magnifier with a point of interest",IDC_STATIC,10,22,110,24
      LTEXT "Usage:\nHide the dialog and choose a place of interest using the mouse. Hold Shift while scrolling to zoom or pan.",IDC_STATIC,10,50,140,60
      DEFPUSHBUTTON "&Close",IDC_CLOSE,60,100,39,12
    DLGEND
    RCEND

    end _tstart
