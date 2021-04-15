;;
;; File: FullscreenMagnifierSample.asm
;;
;; Description: Implements simple UI to control fullscreen magnification, using
;; the Magnification API.
;;

ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0601
endif

include windows.inc
include resource.inc
include magnification.inc
include winres.inc
include stdio.inc
include tchar.inc

option dllimport:none

;; Forward declarations.

SampleDialogProc proto hwndDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
InitDlg proto hwndDlg:HWND
HandleCommand proto hwndDlg:HWND, wCtrlId:WORD
SetZoom proto hwndDlg:HWND, fZoomFactor:real4
SetColorGrayscaleState proto fGrayscaleOn:BOOL
SetInputTransform proto hwndDlg:HWND, fSetInputTransform:BOOL
GetSettings proto hwndDlg:HWND

.data

;; Global variables and strings.

g_pszAppTitle equ <L"Fullscreen Magnifier Sample">

;; Initialize color effect matrices to apply grayscale or restore the colors on
;; the desktop.

g_MagEffectIdentity MAGCOLOREFFECT {{ 1.0,  0.0,  0.0,  0.0,  0.0,
                                      0.0,  1.0,  0.0,  0.0,  0.0,
                                      0.0,  0.0,  1.0,  0.0,  0.0,
                                      0.0,  0.0,  0.0,  1.0,  0.0,
                                      0.0,  0.0,  0.0,  0.0,  1.0 }}

g_MagEffectGrayscale MAGCOLOREFFECT {{ 0.3,  0.3,  0.3,  0.0,  0.0,
                                       0.6,  0.6,  0.6,  0.0,  0.0,
                                       0.1,  0.1,  0.1,  0.0,  0.0,
                                       0.0,  0.0,  0.0,  1.0,  0.0,
                                       0.0,  0.0,  0.0,  0.0,  1.0 }}

.code

;;
;; FUNCTION: WinMain()
;;
;; PURPOSE: Entry point for the application.
;;

wWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE,
        lpCmdLine:LPWSTR, nCmdShow:int_t

    ;; Initialize the magnification functionality for this process.

    .if MagInitialize()

        ;; Present a dialog box to allow the user to control fullscreen
        ;; magnification.

        DialogBox(hInstance,
            MAKEINTRESOURCE(IDD_DIALOG_FULLSCREENMAGNIFICATIONCONTROL),
            NULL, &SampleDialogProc)

        ;; Any current magnification and color effects will be turned off as a
        ;; result of calling MagUninitialize().

        MagUninitialize()

    .else

        MessageBox(NULL, L"Failed to initialize magnification.", g_pszAppTitle, MB_OK)
    .endif

    .return 0
wWinMain endp

;;
;; FUNCTION: SampleDialogProc()
;;
;; PURPOSE: Dialog proc for the UI used for controlling fullscreen magnification.
;;

SampleDialogProc proc hwndDlg:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (uMsg)
    .case WM_INITDIALOG

        InitDlg(hwndDlg)
        .return FALSE

    .case WM_COMMAND

        .if(word ptr wParam[2] == BN_CLICKED)

           .new wCtrlId:WORD = wParam
            HandleCommand(hwndDlg, wCtrlId)
           .return TRUE
        .endif
        .endc

    .case WM_CLOSE

        EndDialog(hwndDlg, 0)
        .return TRUE
    .endsw

    .return FALSE

SampleDialogProc endp

;;
;; FUNCTION: InitDlg()
;;
;; PURPOSE: Initialize the sample dialog box's position and controls.
;;

InitDlg proc hwndDlg:HWND

    ;; Position the dialog box in the center of the primary monitor.

   .new rcDlg:RECT
    GetWindowRect(hwndDlg, &rcDlg)

   .new xDlg:int_t
    GetSystemMetrics(SM_CXSCREEN)
    mov ecx,rcDlg.right
    sub ecx,rcDlg.left
    sub eax,ecx
    shr eax,1
    mov xDlg,eax

   .new yDlg:int_t
    GetSystemMetrics(SM_CYSCREEN)
    mov ecx,rcDlg.bottom
    sub ecx,rcDlg.top
    sub eax,ecx
    shr eax,1
    mov yDlg,eax

    SetWindowPos(hwndDlg, NULL, xDlg, yDlg, 0, 0, SWP_NOZORDER or SWP_NOSIZE)

    ;; Check the "100%" radio box and move focus to it.

   .new hwndControl:HWND = GetDlgItem(hwndDlg, IDC_RADIO_100)
    SendMessage(hwndControl, BM_SETCHECK, BST_CHECKED, 0)
    SetFocus(hwndControl)
    ret

InitDlg endp

;;
;; FUNCTION: HandleCommand()
;;
;; PURPOSE: Take action in response to user action at the dialog box's controls.
;;

HandleCommand proc hwndDlg:HWND, wCtrlId:WORD

    .switch (wCtrlId)

    .case IDC_CLOSE

        ;; Close the sample dialog box.

        EndDialog(hwndDlg, 0)
        .endc

    .case IDC_RADIO_100
    .case IDC_RADIO_200
    .case IDC_RADIO_300
    .case IDC_RADIO_400

        ;; The user clicked one of the radio button to apply some fullscreen
        ;; magnification. (We know the control ids are sequential here.)

       .new fZoomFactor:real4
        movzx eax,wCtrlId
        sub eax,IDC_RADIO_100 - 1
        cvtsi2ss xmm1,eax
        movss fZoomFactor,xmm1
        SetZoom(hwndDlg, fZoomFactor)
        .endc

    .case IDC_CHECK_SETGRAYSCALE

        ;; The user clicked the checkbox to apply grayscale to the colors on
        ;; the screen.

        SendDlgItemMessage(hwndDlg, IDC_CHECK_SETGRAYSCALE, BM_GETCHECK, 0, 0)
        cmp eax,BST_CHECKED
        mov eax,0
        sete al
        SetColorGrayscaleState(eax)
        .endc

    .case IDC_CHECK_SETINPUTTRANSFORM

        ;; The user clicked the checkbox to apply an input transform for touch
        ;; and pen input.

        SendDlgItemMessage(hwndDlg, IDC_CHECK_SETINPUTTRANSFORM, BM_GETCHECK, 0, 0)
        cmp eax,BST_CHECKED
        mov eax,0
        sete al
        SetInputTransform(hwndDlg, eax)
        .endc

    .case IDC_BUTTON_GETSETTINGS

        ;; The user wants to retrieve the current magnification settings.

        GetSettings(hwndDlg)
        .endc
    .endsw
    ret

HandleCommand endp

;;
;; FUNCTION: SetZoom()
;;
;; PURPOSE: Apply fullscreen magnification.
;;

SetZoom proc hwndDlg:HWND, magnificationFactor:real4

    ;; Attempts to apply a magnification of less than 100% will fail.

    movss  xmm0,magnificationFactor
    comiss xmm0,1.0

    .ifnb

        ;; The offsets supplied to MagSetFullscreenTransform() are relative to
        ;; the top left corner of the primary monitor, in unmagnified
        ;; coordinates. To position the top left corner of some window of
        ;; interest at the top left corner of the magnified view, call
        ;; GetWindowRect() to get the window rectangle, and pass the rectangle's
        ;; left and top values as the offsets supplied to
        ;; MagSetFullscreenTransform().

        ;; If the top left corner of the window of interest is to be positioned
        ;; at the top left corner of the monitor furthest to the left of the
        ;; primary monitor, then the top left corner of the virtual desktop
        ;; would be adjusted by the current magnification, as follows:
        ;;   int xOffset = rcTargetWindow.left -
        ;;      (int)(rcVirtualDesktop.left / magnificationFactor);
        ;;   int yOffset = rcTargetWindow.top  -
        ;;      (int)(rcVirtualDesktop.top  / magnificationFactor);

        ;; For this sample, keep the sample's UI at the center of the magnified
        ;; view on the primary monitor. In order to do this, it is nececessary
        ;; to adjust the offsets supplied to MagSetFullscreenTransform() based
        ;; on the magnification being applied.

        ;; Note that the calculations in this file which use
        ;; GetSystemMetrics(SM_C*SCREEN) assume that the values returned from
        ;; that function are unaffected by the current DPI setting. In order to
        ;; ensure this, the manifest for this app declares the app to be DPI
        ;; aware.

       .new xDlg:int_t

        GetSystemMetrics(SM_CXSCREEN) ; * (1.0 - (1.0 / magnificationFactor)) / 2.0
        movss       xmm0,1.0
        movss       xmm1,xmm0
        divss       xmm1,magnificationFactor
        subss       xmm0,xmm1
        cvtsi2ss    xmm1,eax
        mulss       xmm0,xmm1
        divss       xmm0,2.0
        cvtss2si    eax,xmm0
        mov         xDlg,eax

       .new yDlg:int_t

        GetSystemMetrics(SM_CYSCREEN) ; * (1.0 - (1.0 / magnificationFactor)) / 2.0
        movss       xmm0,1.0
        movss       xmm1,xmm0
        divss       xmm1,magnificationFactor
        subss       xmm0,xmm1
        cvtsi2ss    xmm1,eax
        mulss       xmm0,xmm1
        divss       xmm0,2.0
        cvtss2si    eax,xmm0
        mov         yDlg,eax

        .new fSuccess:BOOL = MagSetFullscreenTransform(magnificationFactor, xDlg, yDlg)
        .if (fSuccess)

            ;; If an input transform for pen and touch is currently applied,
            ;; update the transform to account for the new magnification.

            .new fInputTransformEnabled:BOOL
            .new rcInputTransformSource:RECT
            .new rcInputTransformDest:RECT

            .if (MagGetInputTransform(&fInputTransformEnabled,
                    &rcInputTransformSource, &rcInputTransformDest))

                .if (fInputTransformEnabled)

                    SetInputTransform(hwndDlg, fInputTransformEnabled)
                .endif
            .endif
        .endif
    .endif
    ret

SetZoom endp

;;
;; FUNCTION: SetColorGrayscaleState()
;;
;; PURPOSE: Either apply grayscale to all colors on the screen, or restore the
;; original colors.
;;

SetColorGrayscaleState proc fGrayscaleOn:BOOL

    ;; Apply the color matrix required to either invert the screen colors or to
    ;; show the regular colors.

    lea rcx,g_MagEffectIdentity
    .if fGrayscaleOn

        lea rcx,g_MagEffectGrayscale
    .endif

   .new pEffect:PMAGCOLOREFFECT = rcx
    MagSetFullscreenColorEffect(pEffect)
    ret

SetColorGrayscaleState endp

;;
;; FUNCTION: SetInputTransform()
;;
;; PURPOSE: Apply an input transform to allow touch and pen input to account
;;          for the current fullscreen or lens magnification.
;;

SetInputTransform proc hwndDlg:HWND, fSetInputTransform:BOOL

    .new fContinue:BOOL = TRUE

    .new rcSource:RECT = {0}
    .new rcDest:RECT   = {0}

    ;; MagSetInputTransform() is used to adjust pen and touch input to account
    ;; for the current magnification. The "Source" and "Destination" rectangles
    ;; supplied to MagSetInputTransform() are from the perspective of the
    ;; currently magnified visuals. The source rectangle is the portion of the
    ;; screen that is currently being magnified, and the destination rectangle
    ;; is the area on the screen which shows the magnified results.

    ;; If we're setting an input transform, base the transform on the current
    ;; fullscreen magnification.

    .if (fSetInputTransform)

        ;; Assume here the touch and pen input is going to the primary monitor.

        mov rcDest.right,  GetSystemMetrics(SM_CXSCREEN)
        mov rcDest.bottom, GetSystemMetrics(SM_CYSCREEN)

        .new magnificationFactor:real4
        .new xOffset:int_t
        .new yOffset:int_t

        ;; Get the currently active magnification.

        .if MagGetFullscreenTransform(&magnificationFactor, &xOffset, &yOffset)

            ;; Determine the area of the screen being magnified.

            mov rcSource.left,   xOffset
            mov rcSource.top,    yOffset
            mov rcSource.right,  rcSource.left
            mov rcSource.bottom, rcSource.top

            cvtsi2ss xmm0,rcDest.right
            divss    xmm0,magnificationFactor
            cvtss2si eax,xmm0
            add      rcSource.right,eax

            cvtsi2ss xmm0,rcDest.bottom
            divss    xmm0,magnificationFactor
            cvtss2si eax,xmm0
            add      rcSource.bottom,eax

        .else

            ;; An unexpected error occurred trying to get the current magnification.

            mov fContinue,FALSE

            .new dwErr:DWORD = GetLastError()
            .new szError[256]:WCHAR

            swprintf(&szError, L"Failed to get current magnification. Error was %d", dwErr)

            MessageBox(hwndDlg, &szError, g_pszAppTitle, MB_OK)
        .endif
    .endif

    .if (fContinue)

        ;; Now set the input transform as required.
        .if !MagSetInputTransform(fSetInputTransform, &rcSource, &rcDest)

            .new dwErr:DWORD = GetLastError()

            ;; If the last error is E_ACCESSDENIED, then this may mean that the
            ;; process is not running with UIAccess privileges. UIAccess is
            ;; required in order for MagSetInputTransform() to success.

            .new szError[256]:WCHAR
            swprintf(&szError, L"Failed to set input transform. Error was %d", dwErr)
            MessageBox(hwndDlg, &szError, g_pszAppTitle, MB_OK)
        .endif
    .endif
    ret

SetInputTransform endp

;;
;; FUNCTION: GetSettings()
;;
;; PURPOSE: Query all the related settings, and present them to the user.
;;

GetSettings proc hwndDlg:HWND

    .new magnificationLevel:real4
    .new xOffset:int_t
    .new yOffset:int_t
    .new pszColorStatus:LPWSTR = NULL
    .new fInputTransformEnabled:BOOL = FALSE
    .new rcInputTransformSource:RECT
    .new rcInputTransformDest:RECT

    ;; If any unexpected errors occur trying to get the current settings,
    ;; present no settings data.

    .new fSuccess:BOOL = TRUE

    ;; Get the current magnification level and offset.

    .if (!MagGetFullscreenTransform(&magnificationLevel, &xOffset, &yOffset))

        mov fSuccess,FALSE
    .endif

    .if (fSuccess)

        ;; Get the current color effect.

        .new magEffect:MAGCOLOREFFECT
        .if (MagGetFullscreenColorEffect(&magEffect))

            ;; Present friendly text relating to the color effect.

            .if (memcmp(&g_MagEffectIdentity, &magEffect, sizeof(magEffect)) == 0)

                mov pszColorStatus,&@CStr(L"Identity")

            .elseif (memcmp(&g_MagEffectGrayscale, &magEffect,
                sizeof(magEffect)) == 0)

                mov pszColorStatus,&@CStr(L"Grayscale")

            .else

                ;; This would be an unexpected result from MagGetDesktopColorEffect()
                ;; given that the sample only sets the identity or grayscale effects.

                mov pszColorStatus,&@CStr(L"Unknown")
            .endif

        .else

            mov fSuccess,FALSE
        .endif
    .endif

    .if (fSuccess)

        ;; Get the current input transform.

        .if !MagGetInputTransform(&fInputTransformEnabled,
                &rcInputTransformSource, &rcInputTransformDest)

            mov fSuccess,FALSE
        .endif
    .endif

    ;; Present the results of all the calls above.

    .new szMessage[256]:WCHAR

    .if (fSuccess)

        swprintf(&szMessage,
            L"The current settings are:\r\n\r\nMagnification level: %f\r\n"
            "Color effect: %s\r\nInput transform state: %d",
            magnificationLevel, pszColorStatus, fInputTransformEnabled)

    .else

        .new dwErr:DWORD = GetLastError()
        swprintf(&szMessage,
            L"Failed to get magnification setting. Error was %d", dwErr)
    .endif

    MessageBox(hwndDlg, &szMessage, g_pszAppTitle, MB_OK)
    ret

GetSettings endp

RCBEGIN

    RCTYPES 1
    RCENTRY RT_DIALOG
    RCENUMN 1
    RCENUMX IDD_DIALOG_FULLSCREENMAGNIFICATIONCONTROL
    RCLANGX LANGID_US

    STYLE equ DS_SETFONT or DS_MODALFRAME or DS_FIXEDSYS or WS_POPUP or \
              WS_CAPTION or WS_SYSMENU

    DLGBEGIN STYLE, 9, 0, 0, 174, 94
     CAPTION "Fullscreen Magnifier Sample"
     FONT 8, "MS Shell Dlg", 400, 0, 1
      LTEXT "Set the current magnification factor:",IDC_STATIC,7,7,118,8
      CONTROL "&100%",IDC_RADIO_100,RC_BUTTON,BS_AUTORADIOBUTTON or WS_TABSTOP,\
            7,18,35,10
      CONTROL "&200%",IDC_RADIO_200,RC_BUTTON,BS_AUTORADIOBUTTON,47,18,35,10
      CONTROL "&300%",IDC_RADIO_300,RC_BUTTON,BS_AUTORADIOBUTTON,87,18,35,10
      CONTROL "&400%",IDC_RADIO_400,RC_BUTTON,BS_AUTORADIOBUTTON,127,18,35,10
      CONTROL "&Apply grayscale",IDC_CHECK_SETGRAYSCALE,RC_BUTTON,\
            BS_AUTOCHECKBOX or WS_TABSTOP,7,41,100,10
      CONTROL "&Set input transform",IDC_CHECK_SETINPUTTRANSFORM,RC_BUTTON,\
            BS_AUTOCHECKBOX or WS_TABSTOP,7,57,87,10
      PUSHBUTTON "&Get the current settings",IDC_BUTTON_GETSETTINGS,7,73,93,14
      DEFPUSHBUTTON "&Close",IDC_CLOSE,117,73,50,14
    DLGEND

RCEND

    end _tstart
